#include "power_interface.h"
#include <fstream> 
//#include <string>
//#include <iostream>
#include <streambuf> 
void output_parameters_init(string filename)
{
	ofstream oFile; 
	oFile.open(filename, ios::out | ios::app);    
	oFile<<"init_mcpat has been executed once!"<<endl;
	oFile.close(); 
}
string int_to_string(unsigned int num[], int length)
{
	//int length = sizeof(num)/sizeof(int);
	
	string result = "";
	for(int i = 0; i < length; i++)
	{
		int temp = num[i];
		result = result + " " + std::to_string(temp);
	}
	return result;
	
}
string float_to_string(float num[], int length)
{
	//int length = sizeof(num)/sizeof(int);
	
	string result = "";
	for(int i = 0; i < length; i++)
	{
		float temp = num[i];
		result = result + " " + std::to_string(temp);
	}
	return result;
	
}
string double_to_string(double num[], int length)
{
	//int length = sizeof(num)/sizeof(int);
	
	string result = "";
	for(int i = 0; i < length; i++)
	{
		double temp = num[i];
		result = result + " " + std::to_string(temp);
	}
	return result;
	
}
void output_parameters(string filename, string all_parameters)
{
	ofstream oFile; 
	oFile.open(filename, ios::out | ios::app);    
	oFile<<all_parameters;
	oFile.close();
}
void output_bool_parameters(string filename, bool lanes)
{
	// this file is to output only one parameter
	ofstream oFile; 
	oFile.open(filename, ios::out | ios::app);  
	if(lanes)
	{
		oFile<<" "<<"1"<<" ";
	} 
	else
	{
		oFile<<" "<<"0"<<" ";
	} 
	oFile.close();
}
void init_mcpat(const gpgpu_sim_config &config, class gpgpu_sim_wrapper *wrapper, unsigned stat_sample_freq, unsigned tot_inst, unsigned inst){
	string filename = "cycle_parameters.csv";
	output_parameters_init(filename);
	wrapper->init_mcpat(config.g_power_config_name, config.g_power_filename, config.g_power_trace_filename,
	    			config.g_metric_trace_filename,config.g_steady_state_tracking_filename,config.g_power_simulation_enabled,
	    			config.g_power_trace_enabled,config.g_steady_power_levels_enabled,config.g_power_per_cycle_dump,
	    			config.gpu_steady_power_deviation,config.gpu_steady_min_period,config.g_power_trace_zlevel,
	    			tot_inst+inst,stat_sample_freq
	    			);

}
//TODO 14 Aug 2018 called in every GPU clock cycle: 
void mcpat_cycle(const gpgpu_sim_config &config, const struct shader_core_config *shdr_config, class gpgpu_sim_wrapper *wrapper, class power_stat_t *power_stats, unsigned stat_sample_freq, unsigned tot_cycle, unsigned cycle, unsigned tot_inst, unsigned inst){
	static bool mcpat_init=true;
	//if(mcpat_init){ // If first cycle, don't have any power numbers yet
	//	mcpat_init=false;
	//	return;
	//}
	//if ((tot_cycle+cycle) % stat_sample_freq == 0) { //TODO 10 Nov 2018 check if (tot_cycle+cycle) % stat_sample_freq==# rows in output
		//my_start_1
	string filename = "cycle_parameters.csv";
	bool gpgpu_clock_gated_lanes_mimic = shdr_config->gpgpu_clock_gated_lanes;
	unsigned int stat_sample_freq_mimic = stat_sample_freq;//Here I set 500 first.
	unsigned int power_stats_get_total_inst_mimic = power_stats->get_total_inst();
	unsigned int power_stats_get_total_int_inst_mimic = power_stats->get_total_int_inst();
	unsigned int power_stats_get_total_fp_inst_mimic = power_stats->get_total_fp_inst();
	unsigned int power_stats_get_l1d_read_accesses_mimic = power_stats->get_l1d_read_accesses();
	unsigned int power_stats_get_l1d_write_accesses_mimic = power_stats->get_l1d_write_accesses();
	unsigned int power_stats_get_committed_inst_mimic = power_stats->get_committed_inst();
	
	output_bool_parameters(filename, gpgpu_clock_gated_lanes_mimic);
	unsigned int temp_output1[] = {stat_sample_freq_mimic,power_stats_get_total_inst_mimic,power_stats_get_total_int_inst_mimic,power_stats_get_total_fp_inst_mimic,power_stats_get_l1d_read_accesses_mimic,power_stats_get_l1d_write_accesses_mimic,power_stats_get_committed_inst_mimic};
	
	output_parameters(filename, int_to_string(temp_output1,sizeof(temp_output1)/sizeof(unsigned int)) + " ");
	wrapper->set_inst_power(gpgpu_clock_gated_lanes_mimic,stat_sample_freq_mimic, stat_sample_freq_mimic,power_stats_get_total_inst_mimic, power_stats_get_total_int_inst_mimic,power_stats_get_total_fp_inst_mimic, power_stats_get_l1d_read_accesses_mimic,power_stats_get_l1d_write_accesses_mimic, power_stats_get_committed_inst_mimic);
	
	
	
	
	
			//my_end_1
       //shdr_config->gpgpu_clock_gated_lanes,stat_sample_freq, stat_sample_freq,power_stats->get_total_inst(), power_stats->get_total_int_inst(),power_stats->get_total_fp_inst(), power_stats->get_l1d_read_accesses(),power_stats->get_l1d_write_accesses(), power_stats->get_committed_inst());
		// Single RF for both integer and fp ops
	//my_start_2
	unsigned int power_stats_get_regfile_reads_mimic = power_stats->get_regfile_reads();
	unsigned int power_stats_get_regfile_writes_mimic = power_stats->get_regfile_writes();
	unsigned int power_stats_get_non_regfile_operands_mimic = power_stats->get_non_regfile_operands();
	
	unsigned int temp_output2[] = {power_stats_get_regfile_reads_mimic,power_stats_get_regfile_writes_mimic,power_stats_get_non_regfile_operands_mimic};
	
	output_parameters(filename, int_to_string(temp_output2,sizeof(temp_output2)/sizeof(unsigned int)) + " ");
	wrapper->set_regfile_power(power_stats_get_regfile_reads_mimic, power_stats_get_regfile_writes_mimic, power_stats_get_non_regfile_operands_mimic);
	
	//my_end_2

		//Instruction cache stats
	//wrapper->set_icache_power(power_stats->get_inst_c_hits(), power_stats->get_inst_c_misses());
	//my_start_3
	
	unsigned int power_stats_get_inst_c_hits_mimic=power_stats->get_inst_c_hits();
	unsigned int power_stats_get_inst_c_misses_mimic=power_stats->get_inst_c_misses();
	unsigned int temp_output3[] = {power_stats_get_inst_c_hits_mimic, power_stats_get_inst_c_misses_mimic};
	output_parameters(filename, int_to_string(temp_output3,sizeof(temp_output3)/sizeof(unsigned int)) + " ");
	wrapper->set_icache_power(power_stats->get_inst_c_hits(), power_stats->get_inst_c_misses());
	

	//my_end_3



	//Constant Cache, shared memory, texture cache
	//my_start_4
	unsigned int power_stats_get_constant_c_hits_mimic = power_stats->get_constant_c_hits();
	unsigned int power_stats_get_constant_c_misses_mimic = power_stats->get_constant_c_misses();
	unsigned int temp_output4[] = {power_stats_get_constant_c_hits_mimic,power_stats_get_constant_c_misses_mimic};
	output_parameters(filename, int_to_string(temp_output4,sizeof(temp_output4)/sizeof(unsigned int)) + " ");
	
	wrapper->set_ccache_power(power_stats_get_constant_c_hits_mimic, power_stats_get_constant_c_misses_mimic);
	//my_end_4
	
	//my_start_5
	unsigned int power_stats_get_texture_c_hits_mimic = power_stats->get_texture_c_hits();
	unsigned int power_stats_get_texture_c_misses_mimic = power_stats->get_texture_c_misses();
	unsigned int temp_output5[] = {power_stats_get_texture_c_hits_mimic,power_stats_get_texture_c_misses_mimic};
	output_parameters(filename, int_to_string(temp_output5,sizeof(temp_output5)/sizeof(unsigned int)) + " ");
	wrapper->set_tcache_power(power_stats_get_texture_c_hits_mimic, power_stats_get_texture_c_misses_mimic);
	//my_end_5
	
	//my_start_6
	unsigned int power_stats_get_shmem_read_access_mimic = power_stats->get_shmem_read_access();
	unsigned int temp_output6[] = {power_stats_get_shmem_read_access_mimic};
	output_parameters(filename, int_to_string(temp_output6,sizeof(temp_output6)/sizeof(unsigned int)) + " ");
	
	wrapper->set_shrd_mem_power(power_stats_get_shmem_read_access_mimic);
	//my_end_6
	//my_start_7
	
	unsigned int power_stats_get_l1d_read_hits_mimic =power_stats->get_l1d_read_hits();
	unsigned int power_stats_get_l1d_read_misses_mimic  = power_stats->get_l1d_read_misses();
	unsigned int power_stats_get_l1d_write_hits_mimic = power_stats->get_l1d_write_hits();
	unsigned int power_stats_get_l1d_write_misses_mimic = power_stats->get_l1d_write_misses();
	unsigned int temp_output7[] = {power_stats_get_l1d_read_hits_mimic, power_stats_get_l1d_read_misses_mimic, power_stats_get_l1d_write_hits_mimic, power_stats_get_l1d_write_misses_mimic};
	output_parameters(filename, int_to_string(temp_output7,sizeof(temp_output7)/sizeof(unsigned int)) + " ");
	wrapper->set_l1cache_power(power_stats_get_l1d_read_hits_mimic, power_stats_get_l1d_read_misses_mimic,
			power_stats_get_l1d_write_hits_mimic, power_stats_get_l1d_write_misses_mimic);
	//my_end_7
	//my_start_8
	unsigned int power_stats_get_l2_read_hits_mimic = power_stats->get_l2_read_hits();
	unsigned int power_stats_get_l2_read_missess_mimic = power_stats->get_l2_read_misses();
	unsigned int power_stats_get_l2_write_hits_mimic = power_stats->get_l2_write_hits();
	unsigned int power_stats_get_l2_write_misses_mimic = power_stats->get_l2_write_misses();
	unsigned int temp_output8[] = {power_stats_get_l2_read_hits_mimic,power_stats_get_l2_read_missess_mimic,power_stats_get_l2_write_hits_mimic,power_stats_get_l2_write_misses_mimic};
	output_parameters(filename, int_to_string(temp_output8,sizeof(temp_output8)/sizeof(unsigned int)) + " ");
	wrapper->set_l2cache_power(power_stats_get_l2_read_hits_mimic, power_stats_get_l2_read_missess_mimic,
			power_stats_get_l2_write_hits_mimic, power_stats_get_l2_write_misses_mimic);
	
	//my_end_8

	//my_start_9
	float active_sms=(*power_stats->m_active_sms)/stat_sample_freq;
	float num_cores = shdr_config->num_shader();
	float num_idle_core = num_cores - active_sms;
	float temp_output9[] = {num_idle_core};
	output_parameters(filename, float_to_string(temp_output9,sizeof(temp_output9)/sizeof(float)) + " ");
	wrapper->set_idle_core_power(num_idle_core);
	//my_end_9

	//pipeline power - pipeline_duty_cycle *= percent_active_sms;
	//my_start_10
	float pipeline_duty_cycle=((*power_stats->m_average_pipeline_duty_cycle/( stat_sample_freq)) < 0.8)?((*power_stats->m_average_pipeline_duty_cycle)/stat_sample_freq):0.8;
	float temp_output10[] = {pipeline_duty_cycle};
	output_parameters(filename, float_to_string(temp_output10,sizeof(temp_output10)/sizeof(float)) + " ");
	wrapper->set_duty_cycle_power(pipeline_duty_cycle);
	
	//my_end_10
		//Memory Controller
	//my_start_11
	unsigned int power_stats_get_dram_rd_mimic = power_stats->get_dram_rd();
	unsigned int power_stats_get_dram_wr_mimic = power_stats->get_dram_wr();
	unsigned int power_stats_get_dram_pre_mimic = power_stats->get_dram_pre();
	unsigned int temp_output11[] = {power_stats_get_dram_rd_mimic,power_stats_get_dram_wr_mimic,power_stats_get_dram_pre_mimic};
	output_parameters(filename, int_to_string(temp_output11,sizeof(temp_output11)/sizeof(unsigned int)) + " ");
	wrapper->set_mem_ctrl_power(power_stats_get_dram_rd_mimic, power_stats_get_dram_wr_mimic, power_stats_get_dram_pre_mimic);
	
	
	//my_end_11
	//TODO 10 Nov 2018 this is where we set the power for inexact FPUs Execution pipeline accesses FPU (SP) accesses, Integer ALU (not present in Tesla)
	
	//my_start_12
	unsigned int power_stats_get_tot_fpu_accessess_mimic =  power_stats->get_tot_fpu_accessess();
	unsigned int power_stats_get_ialu_accessess_mimic = power_stats->get_ialu_accessess(); 
	unsigned int power_stats_get_tot_sfu_accessess_mimic = power_stats->get_tot_sfu_accessess();
	unsigned int temp_output12[] = {power_stats_get_tot_fpu_accessess_mimic,power_stats_get_ialu_accessess_mimic,power_stats_get_tot_sfu_accessess_mimic};
	output_parameters(filename, int_to_string(temp_output12,sizeof(temp_output12)/sizeof(unsigned int)) + " ");
	
	wrapper->set_exec_unit_power(power_stats_get_tot_fpu_accessess_mimic, power_stats_get_ialu_accessess_mimic, power_stats_get_tot_sfu_accessess_mimic);
	
	
	//my_end_12
	//Average active lanes for sp and sfu pipelines
	
	//my_start_13
	float avg_sp_active_lanes=(power_stats->get_sp_active_lanes())/stat_sample_freq;
	float avg_sfu_active_lanes=(power_stats->get_sfu_active_lanes())/stat_sample_freq;
	assert(avg_sp_active_lanes<=32);
	assert(avg_sfu_active_lanes<=32);
	float temp_output13[] = {avg_sp_active_lanes, avg_sfu_active_lanes};
	output_parameters(filename, float_to_string(temp_output13,sizeof(temp_output13)/sizeof(float)) + " ");
	wrapper->set_active_lanes_power((power_stats->get_sp_active_lanes())/stat_sample_freq,
			(power_stats->get_sfu_active_lanes())/stat_sample_freq);
	//my_end_13

	//my_start_14
	double n_icnt_simt_to_mem = (double)power_stats->get_icnt_simt_to_mem(); // # flits from SIMT clusters to memory partitions
	double n_icnt_mem_to_simt = (double)power_stats->get_icnt_mem_to_simt(); // # flits from memory partitions to SIMT clusters
	double temp_output14[] = {n_icnt_simt_to_mem,n_icnt_mem_to_simt};
	output_parameters(filename, double_to_string(temp_output14, sizeof(temp_output14)/sizeof(double))+" ");
	wrapper->set_NoC_power(n_icnt_mem_to_simt, n_icnt_simt_to_mem); // Number of flits traversing the interconnect
		//my_end_14

	//my_start_15
	
	//output_parameters(filename, " a new cycle!\n");//one cycle one line
	output_parameters(filename, "\n");
	//my_end_15
	wrapper->compute(); //TODO 10 Nov 2018
	wrapper->update_components_power(); //TODO 10 Nov 2018 this will ->update_coefficients so a way to vary coefficients of FUs
	wrapper->print_trace_files();
	power_stats->save_stats();
	wrapper->detect_print_steady_state(0,tot_inst+inst);
	wrapper->power_metrics_calculations();//TODO 10 Nov 2018
	wrapper->dump();
	//}
	//wrapper->close_files();
}

void mcpat_reset_perf_count(class gpgpu_sim_wrapper *wrapper){
	wrapper->reset_counters();
}
