#include "cmd.h"
static cmd_struct cmd_tbl[] = {
    /*
     *�������Ľṹ��
     * ������������Ҫ�ڴ˼��ϣ�
     * CMD_ADD("������","����ʹ�÷�������Ϊ�ո�,�����ܲ���˫���ţ�",��Ӧ�����ִ�к�����)
     * ע�����һ������Ҫ���ţ�ǰ��Ķ���Ҫ����
     */
    CMD_ADD("help"," Print all command and usage ",cmd_help_func),
    CMD_ADD("hello","Print hello",cmd_hello_func),
    CMD_ADD("read","Print data by set flag=1",cmd_read_func),
    CMD_ADD("check","check x,y,delta",cmd_check_func),
    CMD_ADD("modify_L","modify paramter",cmd_modify_L_func),
    CMD_ADD("modify_D","modify paramter",cmd_modify_D_func),
    CMD_ADD("reset","reset x,y,delta",cmd_reset_func),
    CMD_ADD("encoder","read encoder data",cmd_read_encoder_func),
    CMD_ADD("time","modify time",cmd_change_time_func),
    CMD_ADD("wave", "show wave", cmd_send_wave_func),
    CMD_ADD("setxy", "setxy", cmd_setxy_func),
    CMD_ADD("show", "show param ", cmd_show_func),
};



char cmd_line[MAX_CMD_LINE_LENGTH + 1];
char *cmd_argv[MAX_ARGC]; 
    
void cmd_init()
{
    for(int i = 0;i < MAX_ARGC;i++){
        cmd_argv[i] = (char *)malloc(MAX_CMD_ARG_LENGTH + 1);//��ȷ���������ݵ��ڴ�ռ䣬���Է���һ��
    }
}
/*
*���������
*/
int cmd_parse(char *cmd_line,int *argc,char *argv[]){
    char c_temp;
    int i = 0,arg_index = 0;
    int arg_cnt = 0;
    c_temp = cmd_line[i++];  
    while(c_temp != '\r'){
        if(c_temp == ' '){
            if(arg_index == 0){   //���������߲����ַ�����һ���ǿո������   
                c_temp = cmd_line[i++];
                continue;
            }
            //�ո�Ϊ������������ķָ���
            if(arg_cnt == MAX_ARGC){   //���������������,�򷵻�
                return -1;
            }
            argv[arg_cnt][arg_index] = 0;
            arg_cnt++;
            arg_index = 0;
            c_temp = cmd_line[i++];
            continue;
        }
        if(arg_index == MAX_CMD_ARG_LENGTH){   //����������ȹ������򱨴���
            return -2;
        }
        argv[arg_cnt][arg_index++] = c_temp;
        c_temp = cmd_line[i++];
    }
    if(arg_cnt == 0 && arg_index == 0){  //���������߲����ǿյģ��򷵻�
        return -3;
    }
    //���һ�������Ľ���û���������whileѭ���н�����
    argv[arg_cnt++][arg_index] = 0;
    *argc = arg_cnt;//������
    return 0;
}

int cmd_exec(int argc,char *argv[]){
    int cmd_index = 0;
    uint32_t cmd_num;
 
    cmd_num = sizeof(cmd_tbl)/sizeof(cmd_tbl[0]);

    if(argc == 0){  //��������ǿյģ��򷵻�
        return -1;
    }
    for(cmd_index = 0;cmd_index < cmd_num;cmd_index++){   //��������
        if(strcmp((char *)(cmd_tbl[cmd_index].cmd_name),(char *)argv[0]) == 0){  //����ҵ��������ִ���������Ӧ�ĺ���
            cmd_tbl[cmd_index].cmd_func(argc,argv);
            memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
            return 0;
        }
    }
    memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
    return -2;
}

void cmd_help_func(int argc,char *argv[]){
     int i;
    uint32_t cmd_num;
    cmd_num = sizeof(cmd_tbl)/sizeof(cmd_tbl[0]);
    if(argc > 1){
        uprintf("msg:\n help�����������\n\n");      
        return;         
    }
    for(i = 0;i < cmd_num;i++){
        uprintf("cmd:%s\nusage:%s\n\n",cmd_tbl[i].cmd_name,cmd_tbl[i].cmd_usage);
    }
}