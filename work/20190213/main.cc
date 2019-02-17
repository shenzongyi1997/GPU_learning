/*/usr/bin/g++-4.8 -std=c++11 -pthread -Wall -g main.cc -I/home/jason/GPGPU-Sim_dev-half2/src/gpgpu-sim/ -I/home/jason/GPGPU-Sim_dev-half2/src/gpuwattch/  -L/home/jason/GPGPU-Sim_dev-half2/lib/gcc-5.4.0/cuda-9010/debug -lcudart -L/home/jason/GPGPU-Sim_dev-half2/build/gcc-5.4.0/cuda-9010/debug/libcuda -lcuda -L/home/jason/GPGPU-Sim_dev-half2/build/gcc-5.4.0/cuda-9010/debug -lgpgpusim -L/home/jason/GPGPU-Sim_dev-half2/build/gcc-5.4.0/cuda-9010/debug/cuda-sim/ -lgpgpu_ptx_sim -L/home/jason/GPGPU-Sim_dev-half2/build/gcc-5.4.0/cuda-9010/debug/gpgpu-sim/ -L/usr/local/lib -lgpu_uarch_sim  -lm -lz -lGL -lboost_regex -lboost_system -lboost_log_setup -lboost_log -lboost_date_time -lboost_thread -lrt -lboost_filesystem -lgmp -lmpfr  -lboost_regex -lboost_system -lboost_log_setup -lboost_log -lboost_date_time -lboost_thread -lrt -lboost_filesystem -lunwind -o main_test
*/
#include "cacti/io.h"
#include <iostream>
#include "xmlParser.h"
#include "XML_Parse.h"
#include "processor.h"
#include "globalvar.h"
#include "version.h"
#include "power_interface.h"
#include "gpgpu_sim_wrapper.h"
using namespace std;
void print_usage(char * argv0);
int main(int argc,char *argv[]){
	class gpgpu_sim_config config;
	class gpgpu_sim_wrapper* m_gpgpusim_wrapper = new gpgpu_sim_wrapper(true,"");
	//parse XML-based interface
	// ParseXML *p1= new ParseXML();
	// p1->parse(fb);
	// Processor proc(p1);
	// proc.displayEnergy(2, plevel);
	// delete p1;
	return 0;
}

void print_usage(char * argv0){
    cerr << "How to use McPAT:" << endl;
    cerr << "  mcpat -infile <input file name>  -print_level < level of details 0~5 >  -opt_for_clk < 0 (optimize for ED^2P only)/1 (optimzed for target clock rate)>"<< endl;
    //cerr << "    Note:default print level is at processor level, please increase it to see the details" << endl;
    exit(1);
}
