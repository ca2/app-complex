#include "dshowcapture.hpp"
#include "common.h"

using namespace DShow;
using namespace std;

struct DShowEncoder {
	video_enc         *context;
	VideoEncoder           encoder;

	VideoEncoderConfig     config;

	const wchar_t          *device;
	video_format           format;
	long long              frameInterval;

	bool                   first = true;
	u8 *        firstPacket;
	u8  *        header;

	inline DShowEncoder(video_enc *context_, const wchar_t *device_)
		: context(context_),
		  device(device_)
	{
      firstPacket = nullptr;
      header = nullptr;
	}

	inline ~DShowEncoder()
	{
		free(firstPacket);
		free(header);
	}

	//inline void ParseFirstPacket(const u8 *data, size_t size);

	inline bool Update(video_data *settings);
	inline bool Encode(struct encoder_frame *frame,
			struct encoder_packet *packet, bool *received_packet);
};

static inline void FindDevice(DeviceId &identification, const wchar_t *name)
{
	vector<DeviceId> devices;
	DShow::VideoEncoder::EnumEncoders(devices);

	for (const DeviceId &device : devices) {
		if (device.name.find(name)>= 0) {
			identification = device;
			break;
		}
	}
}

/*
 * As far as I can tell the devices only seem to support 1024x768 and 1280x720
 * resolutions, so I'm just going to cap it to those resolutions by aspect.
 *
 * XXX: This should really not be hard-coded.  Problem is I don't know how to
 * properly query the encoding capabilities of the devices.
 */
static const double standardAspect = 1024.0 / 768.0;
static const double wideAspect = 1280.0 / 720.0;

inline bool DShowEncoder::Update(video_data *settings)
{
	std::wstring deviceName;
	DeviceId identification;

	FindDevice(identification, device);

	//video_t *video = obs_encoder_video(context);
	//const struct video_output_info *voi = video_output_get_info(video);

	int bitrate            = (int)settings->video_data_get_int("bitrate");
	int keyint_sec         = (int)settings->video_data_get_int("keyint_sec");
	int width              = (int)context->video_enc_get_width();
	int height             = (int)context->video_enc_get_height();

	double aspect = double(width) / double(height);

	if (keyint_sec == 0)
		keyint_sec = 2;
	if (fabs(aspect - standardAspect) < fabs(aspect - wideAspect)) {
		width = 1024;
		height = 768;
	} else {
		width = 1280;
		height = 720;
	}

	int keyint = keyint_sec * context->video_enc_get_fps_num() / context->video_enc_get_fps_den();

	frameInterval = context->video_enc_get_fps_den() * 10000000 / context->video_enc_get_fps_num();

	config.fpsNumerator           = context->video_enc_get_fps_num();
	config.fpsDenominator         = context->video_enc_get_fps_den();
	config.bitrate                = bitrate;
	config.keyframeInterval       = keyint;
	config.cx()                     = width;
	config.cy()                     = height;
	config.name                   = identification.name;
	config.path                   = identification.path;

	first = true;
	firstPacket = (u8 *) malloc(0);
   header = (u8 *)malloc(0);

	deviceName= identification.name;

	std::wstring encoder_name;
	encoder_name =  config.name;
	//blog(LOG_DEBUG, "win-dshow-encoder:\n"
	//		"\tencoder: %s\n"
	//		"\twidth:   %d\n"
	//		"\theight:  %d\n"
	//		"\tfps_num: %d\n"
	//		"\tfps_den: %d",
	//		deviceName->array,
	//		(int)width,
	//		(int)height,
	//		(int)voi->fps_num,
	//		(int)voi->fps_den);

	return encoder.SetConfig(config);
}

static bool UpdateDShowEncoder(void *data, video_data *settings)
{
	DShowEncoder *encoder = reinterpret_cast<DShowEncoder*>(data);

	if (!encoder->context->video_enc_is_active())
		return encoder->Update(settings);

	return true;
}

static inline void *CreateDShowEncoder(video_data *settings,
		video_enc *context, const wchar_t *device)
{
	DShowEncoder *encoder = nullptr;

	try {
		encoder = new DShowEncoder(context, device);
		UpdateDShowEncoder(encoder, settings);

	} catch (const ::string &error) {
		//blog(LOG_FORMATTED_ERROR, "Could not create DirectShow encoder '%s': %s",
		//		obs_encoder_get_name(context), error);
	}

   //	UNUSED_PARAMETER(settings);
	return encoder;
}

static void *CreateC985Encoder(video_data *settings, video_enc *context)
{
	return CreateDShowEncoder(settings, context, L"C985");
}

static void *CreateC353Encoder(video_data *settings, video_enc *context)
{
	return CreateDShowEncoder(settings, context, L"C353");
}

static void DestroyDShowEncoder(void *data)
{
	delete reinterpret_cast<DShowEncoder*>(data);
}

/* the first packet contains the SPS/PPS (header) NALs, so parse the first
 * packet and separate the NALs */
//inline void DShowEncoder::ParseFirstPacket(const u8 *data, size_t size)
//{
//	const u8 *nal_start, *nal_end, *nal_codestart;
//	const u8 *end = data + size;
//	int type;
//
//	nal_start = obs_avc_find_startcode(data, end);
//	nal_end = nullptr;
//	while (nal_end != end) {
//		nal_codestart = nal_start;
//
//		while (nal_start < end && !*(nal_start++));
//
//		if (nal_start == end)
//			break;
//
//		type = nal_start[0] & 0x1F;
//
//		nal_end = obs_avc_find_startcode(nal_start, end);
//		if (!nal_end)
//			nal_end = end;
//
//		if (type == OBS_NAL_SPS || type == OBS_NAL_PPS) {
//			da_push_back_array(header, nal_codestart,
//					nal_end - nal_codestart);
//
//		} else {
//			da_push_back_array(firstPacket, nal_codestart,
//					nal_end - nal_codestart);
//		}
//
//		nal_start = nal_end;
//	}
//}

//inline bool DShowEncoder::Encode(struct encoder_frame *frame,
//		struct encoder_packet *packet, bool *received_packet)
//{
//	unsigned char *frame_data[DSHOW_MAX_PLANES] = {};
//	size_t frame_sizes[DSHOW_MAX_PLANES] = {};
//	EncoderPacket dshowPacket;
//	bool new_packet = false;
//
//	/* The encoders expect YV12, so __swap the chroma planes for encoding */
//	if (format == VIDEO_FORMAT_I420) {
//		frame_data[0] = frame->data[0];
//		frame_data[1] = frame->data[2];
//		frame_data[2] = frame->data[1];
//		frame_sizes[0] = frame->linesize[0] * config.cy();
//		frame_sizes[1] = frame->linesize[2] * config.cy() / 2;
//		frame_sizes[2] = frame->linesize[1] * config.cy() / 2;
//	}
//
//	long long actualPTS = frame->pts * frameInterval;
//
//	bool success = encoder.Encode(frame_data, frame_sizes,
//			actualPTS, actualPTS + frameInterval,
//			dshowPacket, new_packet);
//	if (!success)
//		return false;
//
//	if (new_packet && !!dshowPacket.data && !!dshowPacket.size_i32) {
//		packet->data     = dshowPacket.data;
//		packet->size_i32     = dshowPacket.size_i32;
//		packet->type     = OBS_ENCODER_VIDEO;
//		packet->pts      = dshowPacket.pts / frameInterval;
//		packet->dts      = dshowPacket.dts / frameInterval;
//		packet->keyframe = obs_avc_keyframe(packet->data, packet->size_i32);
//
//		/* first packet must be parsed in order to retrieve header */
//		if (first) {
//			first = false;
//			ParseFirstPacket(packet->data, packet->size_i32);
//			packet->data = firstPacket.array;
//			packet->size = firstPacket.num;
//		}
//
//		*received_packet = true;
//	}
//
//	return true;
//}

static bool DShowEncode(void *data, struct encoder_frame *frame,
		struct encoder_packet *packet, bool *received_packet)
{
	return reinterpret_cast<DShowEncoder*>(data)->Encode(frame, packet,
			received_packet);
}

//static bool GetDShowExtraData(void *data, u8 **extra_data, size_t *size_i32)
//{
//	DShowEncoder *encoder = reinterpret_cast<DShowEncoder*>(data);
//
//	*extra_data = encoder->header.array;
//	*size = encoder->header.num;
//
//	return *size_i32 > 0;
//}
//
//static inline bool ValidResolution(u32 width, u32 height)
//{
//	return (width == 1280 && height == 720) ||
//		(width == 1024 && height == 768);
//}
//
//static void GetDShowVideoInfo(void *data, struct video_scale_info *info)
//{
//	DShowEncoder *encoder = reinterpret_cast<DShowEncoder*>(data);
//	encoder->format = VIDEO_FORMAT_I420;
//
//	if (info->format == VIDEO_FORMAT_I420 &&
//	    ValidResolution(info->width, info->height))
//		return;
//
//	info->format     = VIDEO_FORMAT_I420;
//	info->width      = info->width;
//	info->height     = info->height;
//	info->range      = VIDEO_RANGE_DEFAULT;
//	info->colorspace = VIDEO_CS_DEFAULT;
//
//	double aspect = double(info->width) / double(info->height);
//
//	if (fabs(aspect - standardAspect) < fabs(aspect - wideAspect)) {
//		info->width = 1024;
//		info->height = 768;
//	} else {
//		info->width = 1280;
//		info->height = 720;
//	}
//}
//
//static void GetDShowEncoderDefauts(video_data *settings)
//{
//	obs_data_set_default_int(settings, "bitrate", 1000);
//}
//
//static obs_properties_t *GetDShowEncoderProperties(void *data)
//{
//	obs_properties_t *ppts = obs_properties_create();
//
//	obs_properties_add_int(ppts, "bitrate", obs_module_text("Bitrate"),
//			1000, 60000, 1);
//
//	UNUSED_PARAMETER(data);
//	return ppts;
//}
//
//void RegisterDShowEncoders()
//{
//	obs_encoder_info info  = {};
//	info.type              = OBS_ENCODER_VIDEO;
//	info.codec             = "h264";
//	info.destroy           = DestroyDShowEncoder;
//	info.encode            = DShowEncode;
//	info.update            = UpdateDShowEncoder;
//	info.get_defaults      = GetDShowEncoderDefauts;
//	info.get_properties    = GetDShowEncoderProperties;
//	info.get_extra_data    = GetDShowExtraData;
//	info.get_video_info    = GetDShowVideoInfo;
//
//	vector<DeviceId> devices;
//	DShow::VideoEncoder::EnumEncoders(devices);
//
//	bool foundC985 = false;
//
//	for (const DeviceId &device : devices) {
//		if (!foundC985 && device.name.find(L"C985")>= 0) {
//			info.identification = "dshow_c985_h264";
//			info.get_name = GetC985EncoderName;
//			info.create = CreateC985Encoder;
//			obs_register_encoder(&info);
//			foundC985 = true;
//
//		} else if (device.name.find(L"C353")>= 0) {
//			info.identification = "dshow_c353_h264";
//			info.get_name = GetC353EncoderName;
//			info.create = CreateC353Encoder;
//			obs_register_encoder(&info);
//		}
//	}
//}

int c_video_capture_enum_encoders(wchar_t *** pppszName, wchar_t *** pppszPath)
{

   vector<DeviceId> devices;
   DShow::VideoEncoder::EnumEncoders(devices);

   if (devices.empty())
   {

      return 0;

   }

   *pppszName = (wchar_t **)malloc(sizeof(wchar_t*) * devices.size());
   *pppszPath = (wchar_t **)malloc(sizeof(wchar_t*) * devices.size());

   for (int i = 0; i < devices.size(); i++)
   {

      (*pppszName)[i] = _wcsdup(devices[i].name.c_str());
      (*pppszPath)[i] = _wcsdup(devices[i].name.c_str());

   }

   return devices.size();
}
