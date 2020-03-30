
#include <stitcher/stitcher.h>
#include <stitcher/common.h>
#include <iostream>
#include <algorithm>
//#define TEST_SINGLE_FILE
//std::vector<std::string> image_paths = { "E:/videos/IMG_20191225_150354_00_176.insp" };
//std::string image_output_path = "D:/test3.jpeg";
//#ifdef TEST_SINGLE_FILE
//std::vector<std::string> inputpaths = { "D:/VID_20190925_174132_00_009.insv" };
//#else
//std::vector<std::string> inputpaths = { "E:/videos/ONE X/VID_20191029_141055_00_011.insv","E:/videos/ONE X/VID_20191029_141055_10_011.insv" };
//#endif // TEST_SINGLE_FILE

void process_callback(long lContext, int process, int error) {
    printf("\rprocess = %d%% ", process);
}

void error_callback(long lContext, int error, const char* errinfo) {

}

int main(int argc, char* argv[]) {

    const std::string helpstr =
        "{-help          | default              | print this message            }\n"
        "{-inputs       | None                  | input files                   }\n"
        "{-output       | None                  | out path                      }\n"
        "{-stitch_type  | template              | template/optflow/dynamicstitch}\n"
        "{-hdr_type     | None                  | singleimagehdr/multiimagehdr_mbb/multiimagehdr_mpl}\n"
        "{-bitrate      | same as input vidoe   | the bitrate of ouput file}\n"
        "{-enable_flowstate |                   | open flowstate           }\n"
        "{-output_size  | 1920x1080             | the resolution of output}\n";


    std::vector<std::string> input_paths;
    std::string output_path;

    STITCH_TYPE stitch_type = STITCH_TYPE::TEMPLATE;
    HDR_TYPE hdr_type = HDR_TYPE::ImageHdr_NONE;

    int output_width = 1920;
    int output_height = 1080;
    int output_bitrate = 0;

    bool bEnableFlowState = false;

    for (size_t i = 1;i < argc; i++) {
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
            bEnableFlowState = true;
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

    std::string strExt = input_paths[0].substr(input_paths[0].find_last_of(".") + 1);
    std::transform(strExt.begin(), strExt.end(), strExt.begin(), ::tolower);
    if (strExt == "insp") {
        auto imageStitcher = std::make_shared<ins_media::ImageStitcher>();
        imageStitcher->SetInputPath(input_paths);
        imageStitcher->SetStitchType(stitch_type);
        imageStitcher->SetHDRType(hdr_type);
        imageStitcher->SetOutputPath(output_path);
        imageStitcher->SetOutputSize(output_width, output_height);
        imageStitcher->EnableFlowState(bEnableFlowState);
        imageStitcher->Stitch();
    }
    else if (strExt == "insv") {
        auto videoStitcher = std::make_shared<ins_media::VideoStitcher>();
        videoStitcher->SetInputPath(input_paths);
        videoStitcher->SetOutputPath(output_path);
        videoStitcher->SetStitchType(stitch_type);
        videoStitcher->SetOutputSize(output_width, output_height);
        videoStitcher->SetOutputBitRate(output_bitrate);
        videoStitcher->EnableFlowState(bEnableFlowState);
        videoStitcher->SetStitchProgressCallback(process_callback, 0);
        videoStitcher->SetStitchStateCallback(error_callback, 0);
        videoStitcher->StartStitch();
        getchar();
    }
    return 0;
}