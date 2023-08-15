//
//  avcapture_video_input_callback.h
//  video_input_avfoundation
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/08/23.
//  Copyright © 2023 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


class avcapture_video_input_callback
{
public:

   

   virtual void on_device_connected() = 0;
   virtual void on_device_disconnected() = 0;

   


};


void install_avcapture_video_input_callback(avcapture_video_input_callback * pcallback);
void uninstall_avcapture_video_input_callback(avcapture_video_input_callback * pcallback);
