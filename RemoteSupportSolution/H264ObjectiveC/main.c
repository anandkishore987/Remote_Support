// main.c : Defines the entry point for the console application.
//

#ifdef _WIN32
#include <io.h>       /* _setmode() */
#include <fcntl.h>    /* _O_BINARY */
#endif

#include "stdafx.h"
#include <stdint.h>
#include <stdio.h>
#include <D:\Projects2\Remote_Support\RemoteSupportSolution\H264ObjectiveC\x264.h>


#define FAIL_IF_ERROR( cond, ... )\
do\
{\
    if( cond )\
    {\
        fprintf( stderr, __VA_ARGS__ );\
        goto fail;\
    }\
} while( 0 )

int main(int argc, char **argv)
{
	int width, height;
	x264_param_t param;
	x264_picture_t pic;
	x264_picture_t pic_out;
	x264_t *h;
	int i_frame = 0;
	int i_frame_size;
	x264_nal_t *nal;
	int i_nal;
	//return 0;

#ifdef _WIN32
	_setmode(_fileno(stdin), _O_BINARY);
	_setmode(_fileno(stdout), _O_BINARY);
	_setmode(_fileno(stderr), _O_BINARY);
#endif

	FAIL_IF_ERROR(!(argc > 1), "Example usage: example 352x288 <input.yuv >output.h264\n");
	FAIL_IF_ERROR(2 != sscanf_s(argv[1], "%dx%d", &width, &height), "resolution not specified or incorrect\n");

	/* Get default params for preset/tuning */
	/*if (x264_param_default_preset(&param, "medium", NULL) < 0)
	goto fail;*/

	/* Configure non-default params */
	param.i_bitdepth = 8;
	param.i_csp = X264_CSP_I420;
	param.i_width = width;
	param.i_height = height;
	param.b_vfr_input = 0;
	param.b_repeat_headers = 1;
	param.b_annexb = 1;

#undef fail
#define fail fail2

	h = x264_encoder_open(&param);
	if (!h)
		goto fail;
#undef fail
#define fail fail3

#undef fail
	fail3 :
		  x264_encoder_close(h);
	  fail2:
		  x264_picture_clean(&pic);
	  fail:
		  return -1;
} 