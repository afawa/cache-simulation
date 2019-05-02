#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>

#include "system_setting.h"
#include "cache.h"

static int bsize=0;
static int nsets=0;
static int assoc=0;
unsigned int hit_latency=1;

struct cache_t* cache;

unsigned int blk_access_fn(enum mem_cmd cmd,md_addr_t baddr,int bsize,struct cache_blk_t *blk,tick_t now){
    
    if (cache){
        if(cmd==Read){
            //读入到block中,因为没有数据，这里不做任何操作,返回一个常数代表访存延迟
            return 100;
        }else{
            //从block写入到memory中
            return 100;
        }
    }else{
        printf("no cache !!\n");
        exit(1);
    }

}

void print_help(){
    printf("This is the help of the cache config\n");
    printf("h: help\n");
    printf("s: cache size\n");
    printf("b: block size (s/b must be an integer!)\n");
    printf("a: Associativity\n");
    exit(0);
}

void printf_result(){
    printf("block size:%d \t set number:%d \t associativity:%d \n",bsize,nsets,assoc);
    printf("hits: %lld \n",cache->hits);
    printf("misses: %lld\n",cache->misses);
    printf("miss rate: %lf\n",(double)(cache->misses)/(cache->misses+cache->hits));
}

void cache_setting(int argc,char ** argv,const char * optstr){
    //default config
    bsize=8;
    nsets=4*(1<<10);//cache size 32K
    assoc=1;
    int c;
    long long cache_size=32*(1<<10);
    while((c=getopt(argc,argv,optstr))!=-1){
        switch(c){
            case 'h':
                print_help();
                break;
            case 's': //格式32K,32M这类
                {if(optarg[strlen(optarg)-1]=='K'){
                    cache_size=1<<10;
                }else if (optarg[strlen(optarg)-1]=='M'){
                    cache_size=1<<20;
                }else{
                    printf("the cache size must end with 'K' or 'M'\n");
                    exit(0);
                }
                optarg[strlen(optarg)-1]='\0';
                int temp=atoi(optarg);
                cache_size*=temp;
                printf("cacheSize: %lld\n",cache_size);
                break;}
            case 'b':
                bsize=atoi(optarg);
                printf("block size: %d\n",bsize);
                break;
            case 'a':
                assoc=atoi(optarg);
                printf("associativity: %d\n",assoc);
                break;
            case '?':
                printf("unknow arg\n");
                print_help();
                break;
            default:
                break;
        }
    }
    nsets=cache_size/(bsize*assoc);
}

int main(int argc,char ** argv){
    /*按照参数生成cache*/
    /*参数列表：
     *char *name
     *int nsets
     *int balloc
     *int usize
     *int assoc
     *enum cache_policy policy
     *blk_access_fn
     *hit_latency
     * */
    const char * optstr="hs:b:a:";
    /*
     *h: help
     *s: cache size
     *b: block size
     *a: Associativity
     */
    cache_setting(argc,argv,optstr);
    cache=cache_create("my cache",nsets,bsize,0,0,assoc,LRU,blk_access_fn,hit_latency);
    /*数据处理*/
    FILE *trace=fopen("../trace/2.trace","r");
    if (!trace){
        printf("can't find the trace file\n");
        exit(0);
    }
    char w_r[1];
    long long pos;
    while(!feof(trace)){
        fscanf(trace,"%s%lld",w_r,&pos);
        //w_r write or read
        //pos loaction
        //这里假定每次访存访问1bytes
        if(w_r[0]=='r'){
            cache_access(cache,Read,pos,0,1,0,0,0);
        }else if(w_r[0]=='w'){
            cache_access(cache,Write,pos,0,1,0,0,0);
        }
    }
    printf("done!!!\n");
    printf_result();

}
