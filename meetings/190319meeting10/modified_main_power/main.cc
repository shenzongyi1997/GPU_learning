/*/usr/bin/g++-4.8 -std=c++11 -pthread -Wall -g -I/home/zongyi/GPGPU-Sim-20190208/src/gpuwattch/ main.cc -o test arbiter.o area.o array.o bank.o basic_circuit.o basic_components.o cacti_interface.o component.o core.o crossbar.o decoder.o htree2.o interconnect.o iocontrollers.o io.o logic.o mat.o memoryctrl.o noc.o nuca.o parameter.o processor.o router.o sharedcache.o subarray.o technology.o Ucache.o uca.o wire.o XML_Parse.o xmlParser.o gpgpu_sim_wrapper.o -lz */
#include "cacti/io.h"
#include <iostream>
#include "xmlParser.h"
#include "XML_Parse.h"
#include "processor.h"
#include "globalvar.h"
#include "version.h"
#include "gpgpu_sim_wrapper.h"
#include <fstream>
using namespace std;
ifstream parameters_file;


void print_usage(char * argv0);
void mimic_init_mcpat(class gpgpu_sim_wrapper *wrapper)
{
	//printf("Now mimic_init_mcpat() is running...");
	char * g_power_config_name_mimic = "gpuwattch_gtx480.xml";
	char * g_power_filename_mimic = "gpgpusim_power_report__Mon-Mar-11-14-44-03-2019.log";
	char * g_power_trace_filename_mimic = "gpgpusim_power_trace_report__Wed-Feb-13-13-30-03-2019.log.gz";
	char * g_metric_trace_filename_mimic = "gpgpusim_metric_trace_report__Wed-Feb-13-13-30-03-2019.log.gz";
	char * g_steady_state_tracking_filename_mimic = "gpgpusim_steady_state_tracking_report__Wed-Feb-13-13-30-03-2019.log.gz";
	bool g_power_simulation_enabled_mimic = true;
	bool g_power_trace_enabled_mimic = true;
	bool g_steady_power_levels_enabled_mimic = true;
	bool g_power_per_cycle_dump_mimic = true;
	double  gpu_steady_power_deviation_mimic = 8;
	double  gpu_steady_min_period_mimic = 4;
	int g_power_trace_zlevel_mimic = 6;
	unsigned int tot_inst_mimic = 0;
	unsigned int inst_mimic = 0;
	unsigned int stat_sample_freq_mimic = 500;//	
	wrapper->init_mcpat(g_power_config_name_mimic, g_power_filename_mimic, g_power_trace_filename_mimic,
	    			g_metric_trace_filename_mimic,g_steady_state_tracking_filename_mimic,g_power_simulation_enabled_mimic,
	    			g_power_trace_enabled_mimic,g_steady_power_levels_enabled_mimic,g_power_per_cycle_dump_mimic,
	    			gpu_steady_power_deviation_mimic,gpu_steady_min_period_mimic,g_power_trace_zlevel_mimic,
	    			tot_inst_mimic+inst_mimic,stat_sample_freq_mimic
	    			);
	//printf("mimic_init_mcpat() finished!\n");
}
vector<string> split(string all, char sp)
{
	vector<string> tokens;
	unsigned int begin = 0;
	for(unsigned int i = 0; i < all.length() ; i++)
	{
		if(all[i] == sp)
		{
			tokens.push_back(all.substr(begin, i - begin));
			begin = i + 1;
		}
	}
	if(all[all.length() - 1] != sp && begin != all.length())
	{
		tokens.push_back(all.substr(begin));
	}
	return tokens;
}
void mimic_wrapper_set_inst_power(
	class gpgpu_sim_wrapper *wrapper,
	bool gpgpu_clock_gated_lanes_mimic,
 	unsigned int stat_sample_freq_mimic,
 	unsigned int power_stats_get_total_inst_mimic,
  	unsigned int power_stats_get_total_int_inst_mimic ,
  	unsigned int power_stats_get_total_fp_inst_mimic,	
  	unsigned int power_stats_get_l1d_read_accesses_mimic,
  	unsigned int power_stats_get_l1d_write_accesses_mimic,
  	unsigned int power_stats_get_committed_inst_mimic )
{
	/*bool gpgpu_clock_gated_lanes_mimic = false;
	unsigned int stat_sample_freq_mimic = 1;//Here I set 500 first.
	unsigned int power_stats_get_total_inst_mimic = 288;
	unsigned int power_stats_get_total_int_inst_mimic = 288;
	unsigned int power_stats_get_total_fp_inst_mimic = 0;
	unsigned int power_stats_get_l1d_read_accesses_mimic = 0;
	unsigned int power_stats_get_l1d_write_accesses_mimic = 0;
	unsigned int power_stats_get_committed_inst_mimic = 0;*/
	wrapper->set_inst_power(gpgpu_clock_gated_lanes_mimic,stat_sample_freq_mimic, stat_sample_freq_mimic,power_stats_get_total_inst_mimic, power_stats_get_total_int_inst_mimic,power_stats_get_total_fp_inst_mimic, power_stats_get_l1d_read_accesses_mimic,power_stats_get_l1d_write_accesses_mimic, power_stats_get_committed_inst_mimic);
	
}
void mimic_wrapper_set_regfile_power(
	class gpgpu_sim_wrapper *wrapper,
	unsigned int power_stats_get_regfile_reads_mimic,
	unsigned int power_stats_get_regfile_writes_mimic ,
	unsigned int power_stats_get_non_regfile_operands_mimic)
{
	/*unsigned int power_stats_get_regfile_reads_mimic = 0;
	unsigned int power_stats_get_regfile_writes_mimic = 0;
	unsigned int power_stats_get_non_regfile_operands_mimic = 6912;*/
	wrapper->set_regfile_power(power_stats_get_regfile_reads_mimic,power_stats_get_regfile_writes_mimic , power_stats_get_non_regfile_operands_mimic);
}

void mimic_wrapper_set_icache_power(
	class gpgpu_sim_wrapper *wrapper,
	unsigned int power_stats_get_inst_c_hits_mimic,
	unsigned int power_stats_get_inst_c_misses_mimic)
{
	/*unsigned int power_stats_get_inst_c_misses_mimic=72;
	unsigned int power_stats_get_inst_c_hits_mimic=144;*/
	wrapper->set_icache_power(power_stats_get_inst_c_hits_mimic,power_stats_get_inst_c_misses_mimic);
}
void mimic_wrapper_set_ccache_power(class gpgpu_sim_wrapper *wrapper,
	unsigned int power_stats_get_constant_c_hits_mimic ,
	unsigned int power_stats_get_constant_c_misses_mimic )
{
	/*unsigned int power_stats_get_constant_c_hits_mimic = 216;
	unsigned int power_stats_get_constant_c_misses_mimic = 216;*/
	wrapper->set_ccache_power( power_stats_get_constant_c_hits_mimic, power_stats_get_constant_c_misses_mimic);
}
void mimic_wrapper_set_tcache_power(class gpgpu_sim_wrapper *wrapper,
	unsigned int power_stats_get_texture_c_hits_mimic,
	unsigned int power_stats_get_texture_c_misses_mimic)
{
	/*unsigned int power_stats_get_texture_c_hits_mimic = 0;
	unsigned int power_stats_get_texture_c_misses_mimic = 216;*/
	wrapper->set_tcache_power(power_stats_get_texture_c_hits_mimic, power_stats_get_texture_c_misses_mimic);
}
void mimic_wrapper_set_shrd_mem_power(class gpgpu_sim_wrapper *wrapper,
	unsigned int power_stats_get_shmem_read_access_mimic)
{
	/*unsigned int power_stats_get_shmem_read_access_mimic = 0;*/
	wrapper->set_shrd_mem_power(power_stats_get_shmem_read_access_mimic);
}
void mimic_wrapper_set_l1cache_power(class gpgpu_sim_wrapper *wrapper,
	unsigned int power_stats_get_l1d_read_hits_mimic,
	unsigned int power_stats_get_l1d_read_misses_mimic,
	unsigned int power_stats_get_l1d_write_hits_mimic,
	unsigned int power_stats_get_l1d_write_misses_mimic)
{
	/*unsigned int power_stats_get_l1d_write_hits_mimic = 0;
	unsigned int power_stats_get_l1d_write_misses_mimic = 0;
	unsigned int power_stats_get_l1d_read_misses_mimic = 0;
	unsigned int power_stats_get_l1d_read_hits_mimic =0;
	*/
	wrapper->set_l1cache_power(power_stats_get_l1d_read_hits_mimic,power_stats_get_l1d_read_misses_mimic,
	 		power_stats_get_l1d_write_hits_mimic, power_stats_get_l1d_write_misses_mimic);
}
void mimic_wrapper_set_l2cache_power(class gpgpu_sim_wrapper *wrapper,
	unsigned int power_stats_get_l2_read_hits_mimic,
	unsigned int power_stats_get_l2_read_missess_mimic,
	unsigned int power_stats_get_l2_write_hits_mimic,
	unsigned int power_stats_get_l2_write_misses_mimic)
{
	/*unsigned int power_stats_get_l2_read_hits_mimic = 0;
	unsigned int power_stats_get_l2_read_missess_mimic = 0;
	unsigned int power_stats_get_l2_write_hits_mimic = 0;
	unsigned int power_stats_get_l2_write_misses_mimic = 0;*/
	
	wrapper->set_l2cache_power(power_stats_get_l2_read_hits_mimic, power_stats_get_l2_read_missess_mimic,
	 		power_stats_get_l2_write_hits_mimic, power_stats_get_l2_write_misses_mimic);
}
void mimic_wrapper_set_mem_ctrl_power(class gpgpu_sim_wrapper *wrapper,
	unsigned int power_stats_get_dram_rd_mimic,
	unsigned int power_stats_get_dram_wr_mimic,
	unsigned int power_stats_get_dram_pre_mimic)
{
	/*unsigned int power_stats_get_dram_rd_mimic = 2;
	unsigned int power_stats_get_dram_wr_mimic = 0;
	unsigned int power_stats_get_dram_pre_mimic = 0;*/
	wrapper->set_mem_ctrl_power(power_stats_get_dram_rd_mimic, power_stats_get_dram_wr_mimic, power_stats_get_dram_pre_mimic);
}
void mimic_wrapper_set_exec_unit_power(class gpgpu_sim_wrapper *wrapper,
	unsigned int power_stats_get_tot_fpu_accessess_mimic,
	unsigned int power_stats_get_ialu_accessess_mimic, 
	unsigned int power_stats_get_tot_sfu_accessess_mimic)
{
	/*unsigned int power_stats_get_tot_fpu_accessess_mimic =  0;
	unsigned int power_stats_get_ialu_accessess_mimic = 0; 
	unsigned int power_stats_get_tot_sfu_accessess_mimic = 0;*/
	wrapper->set_exec_unit_power(power_stats_get_tot_fpu_accessess_mimic, power_stats_get_ialu_accessess_mimic, power_stats_get_tot_sfu_accessess_mimic);
	
}
void mimic_wrapper_set_active_lanes_power(class gpgpu_sim_wrapper *wrapper,
	unsigned int stat_sample_freq,
	float power_stats_get_sp_active_lanes_mimic,
	float power_stats_get_sfu_active_lanes_mimic)
{
	/*unsigned int stat_sample_freq = 1;
	float power_stats_get_sp_active_lanes_mimic = 0;
	float power_stats_get_sfu_active_lanes_mimic = 0;*/
	wrapper->set_active_lanes_power((power_stats_get_sp_active_lanes_mimic)/stat_sample_freq,
	 		(power_stats_get_sfu_active_lanes_mimic)/stat_sample_freq);
	
}
void mcpat_cycle(class gpgpu_sim_wrapper * wrapper,unsigned stat_sample_freq, unsigned tot_cycle, unsigned cycle, unsigned tot_inst, unsigned inst){	
	bool gpgpu_clock_gated_lanes_mimic;
	unsigned int stat_sample_freq_mimic,power_stats_get_total_inst_mimic,power_stats_get_total_int_inst_mimic,power_stats_get_total_fp_inst_mimic,power_stats_get_l1d_read_accesses_mimic,power_stats_get_l1d_write_accesses_mimic,power_stats_get_committed_inst_mimic;
	unsigned int power_stats_get_regfile_reads_mimic,power_stats_get_regfile_writes_mimic,power_stats_get_non_regfile_operands_mimic;
	unsigned int power_stats_get_inst_c_hits_mimic, power_stats_get_inst_c_misses_mimic;
	unsigned int power_stats_get_constant_c_hits_mimic,power_stats_get_constant_c_misses_mimic;
	unsigned int power_stats_get_texture_c_hits_mimic,power_stats_get_texture_c_misses_mimic;
	unsigned int power_stats_get_shmem_read_access_mimic;
	unsigned int power_stats_get_l1d_read_hits_mimic, power_stats_get_l1d_read_misses_mimic, power_stats_get_l1d_write_hits_mimic, power_stats_get_l1d_write_misses_mimic;
	unsigned int power_stats_get_l2_read_hits_mimic,power_stats_get_l2_read_missess_mimic,power_stats_get_l2_write_hits_mimic,power_stats_get_l2_write_misses_mimic;
	float num_idle_core;
	float pipeline_duty_cycle;
	unsigned int power_stats_get_dram_rd_mimic,power_stats_get_dram_wr_mimic,power_stats_get_dram_pre_mimic;
	unsigned int power_stats_get_tot_fpu_accessess_mimic,power_stats_get_ialu_accessess_mimic,power_stats_get_tot_sfu_accessess_mimic;
	float avg_sp_active_lanes, avg_sfu_active_lanes;
	double n_icnt_simt_to_mem,n_icnt_mem_to_simt;
	
	parameters_file>>gpgpu_clock_gated_lanes_mimic>>stat_sample_freq_mimic>>power_stats_get_total_inst_mimic>>power_stats_get_total_int_inst_mimic>>power_stats_get_total_fp_inst_mimic>>power_stats_get_l1d_read_accesses_mimic>>power_stats_get_l1d_write_accesses_mimic>>power_stats_get_committed_inst_mimic;
	
	
	mimic_wrapper_set_inst_power(wrapper,gpgpu_clock_gated_lanes_mimic,stat_sample_freq_mimic,power_stats_get_total_inst_mimic,power_stats_get_total_int_inst_mimic,power_stats_get_total_fp_inst_mimic,power_stats_get_l1d_read_accesses_mimic,power_stats_get_l1d_write_accesses_mimic,power_stats_get_committed_inst_mimic);
	
	
	
	//printf("wrapper->set_inst_power has been executed in mimic!\n");
	//wrapper->set_inst_power(0,stat_sample_freq, stat_sample_freq,0, 0,0, 0,0, 0);
	// // Single RF for both integer and fp ops
	
	
	parameters_file>>power_stats_get_regfile_reads_mimic>>	power_stats_get_regfile_writes_mimic>>power_stats_get_non_regfile_operands_mimic;
	
	
	mimic_wrapper_set_regfile_power(wrapper,power_stats_get_regfile_reads_mimic,power_stats_get_regfile_writes_mimic,power_stats_get_non_regfile_operands_mimic);
	
	
	//printf("wrapper->set_regfile_power has been executed in mimic!\n");
	// //Instruction cache stats
	parameters_file>>power_stats_get_inst_c_hits_mimic>> power_stats_get_inst_c_misses_mimic;
	
	mimic_wrapper_set_icache_power(wrapper,power_stats_get_inst_c_hits_mimic, power_stats_get_inst_c_misses_mimic);
	//printf("wrapper->set_icache_power has been executed in mimic!\n");
	
	
	
	// //Constant Cache, shared memory, texture cache
	parameters_file>>power_stats_get_constant_c_hits_mimic>>power_stats_get_constant_c_misses_mimic; 
	mimic_wrapper_set_ccache_power(wrapper,power_stats_get_constant_c_hits_mimic,power_stats_get_constant_c_misses_mimic);
	//printf("wrapper->set_ccache_power has been executed in mimic!\n");	
	parameters_file>>power_stats_get_texture_c_hits_mimic>>power_stats_get_texture_c_misses_mimic;
	mimic_wrapper_set_tcache_power(wrapper,power_stats_get_texture_c_hits_mimic,power_stats_get_texture_c_misses_mimic);
	//printf("wrapper->set_tcache_power has been executed in mimic!\n");	
	
	
	parameters_file>>power_stats_get_shmem_read_access_mimic;
	mimic_wrapper_set_shrd_mem_power(wrapper,power_stats_get_shmem_read_access_mimic);
	//printf("wrapper->set_shrd_mem_power has been executed in mimic!\n");	
	
	
	
	parameters_file>>power_stats_get_l1d_read_hits_mimic>>power_stats_get_l1d_read_misses_mimic>>power_stats_get_l1d_write_hits_mimic>>power_stats_get_l1d_write_misses_mimic;
	mimic_wrapper_set_l1cache_power(wrapper,power_stats_get_l1d_read_hits_mimic,power_stats_get_l1d_read_misses_mimic,power_stats_get_l1d_write_hits_mimic,power_stats_get_l1d_write_misses_mimic);
	//printf("wrapper->set_l1cache_power has been executed in mimic!\n");	
	parameters_file>>power_stats_get_l2_read_hits_mimic>>power_stats_get_l2_read_missess_mimic>>power_stats_get_l2_write_hits_mimic>>power_stats_get_l2_write_misses_mimic;
	mimic_wrapper_set_l2cache_power(wrapper,power_stats_get_l2_read_hits_mimic,power_stats_get_l2_read_missess_mimic,power_stats_get_l2_write_hits_mimic,power_stats_get_l2_write_misses_mimic);
	//printf("wrapper->set_l2cache_power has been executed in mimic!\n");
	// float active_sms=(*power_stats->m_active_sms)/stat_sample_freq;
	//float active_sms = 11.9759998;
	//float num_cores = 15;
	//float num_idle_core = num_cores - active_sms;
	parameters_file>>num_idle_core;
	wrapper->set_idle_core_power(num_idle_core);
	//printf("idle_core_power has been set!\n");
	// //pipeline power - pipeline_duty_cycle *= percent_active_sms;
	//float pipeline_duty_cycle=0;
	parameters_file>>pipeline_duty_cycle;
	wrapper->set_duty_cycle_power(pipeline_duty_cycle);
	//printf("duty_cycle_power has been set!\n");
	// //Memory Controller
	parameters_file>>power_stats_get_dram_rd_mimic>>power_stats_get_dram_wr_mimic>>power_stats_get_dram_pre_mimic;
	mimic_wrapper_set_mem_ctrl_power(wrapper,power_stats_get_dram_rd_mimic,power_stats_get_dram_wr_mimic,power_stats_get_dram_pre_mimic);
	//printf("memory control power has been executed in mimic!\n");
	// //TODO 10 Nov 2018 this is where we set the power for inexact FPUs Execution pipeline accesses FPU (SP) accesses, Integer ALU (not present in Tesla)
	parameters_file>>power_stats_get_tot_fpu_accessess_mimic>>power_stats_get_ialu_accessess_mimic>>power_stats_get_tot_sfu_accessess_mimic;
	mimic_wrapper_set_exec_unit_power(wrapper,power_stats_get_tot_fpu_accessess_mimic,power_stats_get_ialu_accessess_mimic,power_stats_get_tot_sfu_accessess_mimic);
	//printf("exec_unit_power has been set in mimic!");
	// //Average active lanes for sp and sfu pipelines
	//float avg_sp_active_lanes=0;
	//float avg_sfu_active_lanes=0;
	//assert(avg_sp_active_lanes<=32);
	//assert(avg_sfu_active_lanes<=32);
	parameters_file>>avg_sp_active_lanes>>avg_sfu_active_lanes;
	mimic_wrapper_set_active_lanes_power(wrapper,stat_sample_freq_mimic,avg_sp_active_lanes,avg_sfu_active_lanes);
	//printf("active_lanes_power has been set!");
	//double n_icnt_simt_to_mem = 24;//(double)power_stats->get_icnt_simt_to_mem(); // # flits from SIMT clusters to memory partitions
	//double n_icnt_mem_to_simt = 60;//(double)power_stats->get_icnt_mem_to_simt(); // # flits from memory partitions to SIMT clusters
	parameters_file>>n_icnt_simt_to_mem>>n_icnt_mem_to_simt;
	wrapper->set_NoC_power(n_icnt_mem_to_simt, n_icnt_simt_to_mem); // Number of flits traversing the interconnect
	//printf("Noc power has been set!");
	wrapper->compute(); //TODO 10 Nov 2018
	wrapper->update_components_power(); //TODO 10 Nov 2018 this will ->update_coefficients so a way to vary coefficients of FUs
	wrapper->print_trace_files();
	wrapper->detect_print_steady_state(0,0);
	wrapper->power_metrics_calculations();//TODO 10 Nov 2018
	wrapper->dump();
	// wrapper->close_files();
	return;
}
int main(int argc,char *argv[]){
	char xml_filename[] = "gpuwattch_gtx480.xml";
	class gpgpu_sim_wrapper* wrapper = new gpgpu_sim_wrapper(true,xml_filename);
	mimic_init_mcpat(wrapper);
	parameters_file.open("cycle_parameters.csv",ios::in);
	parameters_file.seekg(0, ios_base::end);
    int all_length = parameters_file.tellg();
	parameters_file.seekg(0, ios_base::beg);
	while(!parameters_file.eof())
	{
		mcpat_cycle(wrapper,0,0,0,0,0);
		printf("now we are at %f\n", (double)parameters_file.tellg()/(double)all_length);
	}
	printf("exiting\n");
	parameters_file.close();
	exit(1);
}

void print_usage(char * argv0){
    cerr << "How to use McPAT:" << endl;
    cerr << "  mcpat -infile <input file name>  -print_level < level of details 0~5 >  -opt_for_clk < 0 (optimize for ED^2P only)/1 (optimzed for target clock rate)>"<< endl;
    //cerr << "    Note:default print level is at processor level, please increase it to see the details" << endl;
    exit(1);
}

