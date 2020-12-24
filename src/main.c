#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>

typedef struct {
  uint32_t scheduler[5];
  uint32_t next;
  char extention[4];
} Script_t;
Script_t *Scripts[128];

//TODO: add devide option
//TOOD: add full file name instad of only extention
Script_t *getSchedule(char *str){
  uint8_t is = 0;
  Script_t scit;
  scit.scheduler[0] = 
    scit.scheduler[1] = 
    scit.scheduler[2] = 
    scit.scheduler[3] = 
    scit.scheduler[4] = 0;
  scit.extention[3] = 0;
  int8_t cmd[3];
  cmd[0] = cmd[1] = cmd[2] = 0;
  printf("filename: %s\n", str);

  // read the filename
  for(uint8_t ic=0; ic<strlen(str); ic++){
    switch ((char)*(str+ic)){
      case ' ':
        switch (cmd[0])
        {
          case '-':
            for(uint8_t i=cmd[2]; i>cmd[1]; i--){
              scit.scheduler[is] |= 1<<i;
            }
            break;
          default:
            scit.scheduler[is] |= (is == 0) ? 1<<(cmd[1]/2) : 1<<cmd[1];
            break;
        }
        is++;
        cmd[0] = 0;
        cmd[1] = 0;
        break;
      case '*':
        scit.scheduler[is] = ~0;
        break;
      case '0' ... '9':
        printf("number detected. char: %c, cmd: [%c, %d, %d], ", (char)*(str+ic), cmd[0], cmd[1], cmd[2]);
        if(cmd[0] == '-'){
          cmd[2] *= 10;
          cmd[2] += (char)*(str+ic) - '0';
        }else{
          cmd[1] *= 10;
          cmd[1] += (char)*(str+ic) - '0';
        }
        printf("cmd: [%c, %d, %d]\n", cmd[0], cmd[1], cmd[2]);
        break;
      case ',':
        cmd[0] = ',';
        scit.scheduler[is] |= (is == 0) ? 1<<(cmd[1]/2) : 1<<cmd[1];
        cmd[1] = 0;
        break;
      case '-':
        if(is == 0)
          cmd[1] /= 2;
        cmd[0] = '-';
        break;
    }
    if((char)*(str+ic) == '.'){
      uint8_t i = 0;
      if(ic+3 >= strlen(str)){
        memcpy(&scit.extention, str+ic+1, strlen(str) - ic);
        scit.extention[strlen(str) - ic] = 0;
      }else
        memcpy(&scit.extention, str + strlen(str) - 3, 3);
      break;
    }
    if(is == 5)
      break;
  }
  printf("scheduler: [\n  0x%x\n  0x%x\n  0x%x\n  0x%x\n  0x%x\n]\nextention: %s\n", 
    scit.scheduler[0], 
    scit.scheduler[1], 
    scit.scheduler[2], 
    scit.scheduler[3], 
    scit.scheduler[4],
    scit.extention
  );
}

void getScripts(){
  DIR *ScriptDir = opendir("./scripts");
  uint8_t i=0;
  while(i < 128){
    struct dirent *script = readdir(ScriptDir);

    if(script == NULL)
      break;

    //TODO: add simbolic link suport
    if(script->d_type != DT_REG)
      continue;

    Scripts[i] = getSchedule(script->d_name);
    i++;
  }
}

void main(){
  getScripts();
}