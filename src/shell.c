#include "geo.h"

#define SHELL_BUF_SIZE 50

//maybe we should build the entire system on callback functions
//like this: g_module_install() implemented by each module
//calls geo_generation_register(int gen_type, geo_generation_t f)
//			typedef int (*geo_generation_t) (geo_obj *obj, geo_attr_t *attr, geo_deps *deps)
//		return 1 if generated successfully, and return customized status code if generated it wrong
//		then the status will be passed to 
//			typedef char *(geo_error_t) (geo_obj *obj, geo_attr_t *attr, int statuscode)
//		this function should return a const string predefined.
//      shell_command_register()
//      	typedef 
//      shell_printattr_register()
//      
static const char helpmsg[] =   "Geometry Sketchpad, Revision %d\n"
				"Current Available Commands:\n"
				"add_point -- add a free point to the"; 


void run_shell(void) {
	
	char cmdbuf[SHELL_BUF_SIZE];
	
	printf( "Geometry Sketchpad\n"
		"Interactive Shell\n"
		"Input Command to begin:\n"
		);
	while (1) {
		int c;
		int pbuf = 0;
		char *p;
		pbuf = 0;

		fgets(cmdbuf, SHELL_BUF_SIZE, stdin);


		if ( strcmp(cmdbuf, "help")  == 0) {
			printf( "help -- show this help message\n"
				"add [stu_id] [stu_score_1] ... [stu_score_3] -- add students\n");
			continue;
		}
		if ( strcmp(cmdbuf, "add") == 0 ) {
	
			
			continue;
		}
		if ( strcmp(cmdbuf, "quit") == 0) {
			break;
		}
	}
	
}

