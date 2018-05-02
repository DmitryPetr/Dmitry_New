#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
char* WayNew(char* way, char* path)
    {
        char* newWay = malloc((strlen(way)+strlen(path)+5)*sizeof(char));
        strcpy(newWay,way);
        strcat(newWay,"/");
        strcat(newWay, path);
        return newWay;
    }

int add(int a, int b)
    {
        return a+b;
    }
    
int mul(int a, int b)
    {
        return a*b;
    }
    
int result(char *way, int (*func)(int, int)){
    DIR* dir = opendir(way);
    int res=0;
    if (dir){
        struct  dirent *read = readdir(dir);
        while(read){
            if(strcmp(read->d_name,".")!=0&&strcmp(read->d_name,"..")!=0){
                char* newWay = WayNew(way, read->d_name);
                if(!(strcmp(read->d_name,"add")))
                {
                    res = (*func)(res,result(newWay,&add));
                }
                else if(!(strcmp(read->d_name,"mul")))
                {
                    res = (*func)(res,result(newWay,&mul));
                }
                else res = (*func)(res, result(newWay,func));				
                free(newWay);
            }
            read = readdir(dir);
        }
    } else{
        int val;
        FILE *file = fopen(way,"r");
        while (fscanf(file,"%d ",&val)>0) res = (*func)(res,val);
        fclose(file);
    }
    closedir(dir);
    return res;
}

int main(){
    FILE* file = fopen("result.txt", "w");
    DIR* dir = opendir("./tmp");
    printf("HH\n");
    struct dirent* ValDir = readdir(dir);
    if (!dir){
    printf("ff\n");
    return 0;}
    int res=0;
    if(!strcmp(ValDir->d_name, "add")){
        closedir(dir);
        res = result("./tmp/add", &add);
    }
    if(!strcmp(ValDir->d_name, "mul")){
        closedir(dir);
        res = result("/home/box/tmp/mul", &mul);
    }
    fprintf(file, "%d", res);
    fclose(file);
    return 0;
}
