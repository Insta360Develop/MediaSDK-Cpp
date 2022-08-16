#include <stitcher/stitcher.h>
#include <stitcher/common.h>
#include <iostream>
#include <algorithm>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std::chrono;

const std::string helpstr =
"{-help					| default				| print this message            }\n"
"{-inputs				| None						| input files                   }\n"
"{-output				| None						| out path                      }\n"
"{-stitch_type			| template              | template						}\n"
"{												| optflow						}\n"
"{												| dynamicstitch					}\n"
"{-hdr_type				| None                  | singleimagehdr			    }\n"
"{												| multiimagehdr_mbb				}\n"
"{												| multiimagehdr_mpl				}\n"
"{-bitrate				| same as input vidoe   | the bitrate of ouput file     }\n"
"{-enable_flowstate		| OFF					| open flowstate                }\n"
"{-enable_directionlock | OFF					| open directionlock            }\n"
"{-output_size			| 1920x1080             | the resolution of output	    }\n"
"{-disable_cuda			| true					| disable_cuda				    }\n"
"{-enable_stitchfusion	| OFF					| stitch_fusion				    }\n"
"{-enable_denoise		| OFF					| enable denoise				}\n"
"{-enable_colorplus		| OFF					| enable colorplus				}\n"
"{-colorplus_model		| 						| colorplus_model path			}\n"
"{-gpu_no				| default 0				| gpu number begin with 0	    }\n";

int main(int argc, char* argv[]) {
	std::vector<std::string> input_paths;
	std::string output_path;

	STITCH_TYPE stitch_type = STITCH_TYPE::TEMPLATE;
	HDR_TYPE hdr_type = HDR_TYPE::ImageHdr_NONE;

	int output_width = 1920;
	int output_height = 960;
	int output_bitrate = 0;
	int gpu = 0;

	bool enable_flowstate = false;
	bool enable_cuda = true;
	bool enalbe_stitchfusion = false;
	bool enable_colorplus = false;
	bool enable_directionlock = false;
	bool enable_denoise = false;
	std::string colorpuls_model_path;
	for (size_t i = 1; i < argc; i++) {
		if (std::string("-inputs") == std::string(argv[i])) {
			std::string input_path = argv[++i];
			while (input_path[0] != '-') {
				input_paths.push_back(input_path);
				input_path = argv[++i];
			}
		}

		if (std::string("-output") == std::string(argv[i])) {
			output_path = argv[++i];
		}
		if (std::string("-colorplus_model") == std::string(argv[i])) {
			colorpuls_model_path = argv[++i];
		}
		else if (std::string("-stitch_type") == std::string(argv[i])) {
			std::string stitchType = argv[++i];
			if (stitchType == std::string("optflow")) {
				stitch_type = STITCH_TYPE::OPTFLOW;
			}
			else if (stitchType == std::string("dynamicstitch")) {
				stitch_type = STITCH_TYPE::DYNAMICSTITCH;
			}
		}
		else if (std::string("-enable_flowstate") == std::string(argv[i])) {
			enable_flowstate = true;
		}
		else if (std::string("-disable_cuda") == std::string(argv[i])) {
			enable_cuda = false;
		}
		else if (std::string("-enable_stitchfusion") == std::string(argv[i])) {
			enalbe_stitchfusion = true;
		}
		else if (std::string("-enable_denoise") == std::string(argv[i])) {
			enable_denoise = true;
		}
		else if (std::string("-enable_colorplus") == std::string(argv[i])) {
			enable_colorplus = true;
		}
		else if (std::string("-enable_directionlock") == std::string(argv[i])) {
			enable_directionlock = true;
		}
		else if (std::string("-gpu_no") == std::string(argv[i])) {
			gpu = std::atoi(argv[++i]);
			if (gpu < 0) {
				gpu = 0;
			}
		}
		else if (std::string("-hdr_type") == std::string(argv[i])) {
			std::string HDRType = argv[++i];
			if (HDRType == std::string("singleimagehdr")) {
				hdr_type = HDR_TYPE::SingleImageHdr;
			}
			else if (HDRType == std::string("multiimagehdr_mbb")) {
				hdr_type = HDR_TYPE::MultiImageHdr_mbb;
			}
			else if (HDRType == std::string("multiimagehdr_mpl")) {
				hdr_type = HDR_TYPE::MultiImageHdr_mpl;
			}
		}
		else if (std::string("-bitrate") == std::string(argv[i])) {
			output_bitrate = atoi(argv[++i]);
		}
		else if (std::string("-output_size") == std::string(argv[i])) {
			sscanf(argv[++i], "%dx%d", &output_width, &output_height);
		}
		else if (std::string("-help") == std::string(argv[i])) {
			std::cout << helpstr << std::endl;
		}
	}

	if (input_paths.empty()) {
		std::cout << "can not find input_file" << std::endl;
		std::cout << helpstr << std::endl;
		return -1;
	}

	if (output_path.empty()) {
		std::cout << "can not find output_file" << std::endl;
		std::cout << helpstr << std::endl;
		return -1;
	}

	if (colorpuls_model_path.empty()) {
		enable_colorplus = false;
	}

	std::mutex mutex_;
	std::condition_variable cond_;
	bool is_finisned = false;
	bool has_error = false;
	int stitch_progress = 0;
	int count = 1;
	while (count--) {
		std::string suffix = input_paths[0].substr(input_paths[0].find_last_of(".") + 1);
		std::transform(suffix.begin(), suffix.end(), suffix.begin(), ::tolower);
		if (suffix == "insp" || suffix == "jpg") {
			auto image_stitcher = std::make_shared<ins_media::ImageStitcher>();
			image_stitcher->SetInputPath(input_paths);
			image_stitcher->SetStitchType(stitch_type);
			image_stitcher->SetHDRType(hdr_type);
			image_stitcher->SetOutputPath(output_path);
			image_stitcher->SetOutputSize(output_width, output_height);
			image_stitcher->EnableFlowState(enable_flowstate);
			image_stitcher->EnableDenoise(enable_denoise);
			image_stitcher->EnableColorPlus(enable_colorplus, colorpuls_model_path);
			image_stitcher->Stitch();
		}
		else if (suffix == "insv") {
			auto start_time = steady_clock::now();
			auto video_stitcher = std::make_shared<ins_media::VideoStitcher>();
			video_stitcher->SetInputPath(input_paths);
			video_stitcher->SetOutputPath(output_path);
			video_stitcher->SetStitchType(stitch_type);
			video_stitcher->EnableCuda(enable_cuda);
			video_stitcher->EnableStitchFusion(enalbe_stitchfusion);
			video_stitcher->SetCudaDeviceNo(gpu);
			video_stitcher->EnableColorPlus(enable_colorplus, colorpuls_model_path);
			video_stitcher->SetOutputSize(output_width, output_height);
			video_stitcher->SetOutputBitRate(output_bitrate);
			video_stitcher->EnableFlowState(enable_flowstate);
			video_stitcher->EnableDenoise(enable_denoise);
			video_stitcher->EnableDirectionLock(enable_directionlock);
			video_stitcher->SetStitchProgressCallback([&](int process, int error) {
				if (stitch_progress != process) {
					std::cout << "\r";
					std::cout << "process = " << process;
					stitch_progress = process;
				}

				if (stitch_progress == 100) {
					cond_.notify_one();
					is_finisned = true;
				}
			});

			video_stitcher->SetStitchStateCallback([&](int error, const char* errinfo) {
				has_error = true;
				cond_.notify_one();
			});

			video_stitcher->StartStitch();

			std::unique_lock<std::mutex> lck(mutex_);
			cond_.wait(lck, [&] {
				return (video_stitcher->GetStitchProgress() == 100 && is_finisned) || has_error;
			});
           
			auto end_time = steady_clock::now();
			std::cout << "cost = " << duration_cast<duration<double>>(end_time - start_time).count() << std::endl;
		}
	}
	return 0;
}