#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "limits.h"
#include "list.h"
#include "hash.h"
#include "bitmap.h"


int main()
{
    char command[CHAR_MAX], *line;
    struct list_name* list_names=NULL;
    struct bitmap_name* bitmap_names=NULL;
    struct hash_name* hash_names=NULL;
    int counts = 0;

    while(1)
    {   
        /*command 한줄 받아오기*/
        fgets(command, CHAR_MAX, stdin);
        command[strlen(command) - 1] = '\0';

        /*첫번째 단어 받기*/
        char* token = strtok(command, " ");
        /*create*/
        if(strcmp(token, "create")==0)
        {
            token = strtok(NULL, " ");
            /*list_create*/
            if(strcmp(token, "list")==0)
            {   
                struct list * tmp = list_create();

                token = strtok(NULL, " ");
                if(list_names==NULL)
                    list_names = (struct list_name *)malloc(sizeof(struct list_name)*100);
                
                list_names[counts].name = strdup(token);
                list_names[counts].list = tmp;
                counts++;
                
            }

            /*hashtable_create*/
            else if(strcmp(token, "hashtable")==0)
            {
                struct hash * tmp = create_hash();

                token = strtok(NULL, " ");
                if(hash_names==NULL)
                    hash_names = (struct list_name *)malloc(sizeof(struct list_name)*100);
                
                hash_names[counts].name = strdup(token);
                hash_names[counts].hash = tmp;
                counts++;
            }

            /*bitmap_create */
            else if(strcmp(token, "bitmap")==0)
            {   
                struct bitmap * tmp;
                if(bitmap_names==NULL)
                    bitmap_names = (struct bitmap_name *)malloc(sizeof(struct bitmap_name)*100);

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                /*값 불러오기*/
                token = strtok(NULL, " ");
                size_t cnt = atoi(token);

                tmp = bitmap_create(cnt);

                bitmap_names[counts].name = strdup(name);
                bitmap_names[counts].bitmap = tmp;
                counts++;   
            }


        }

        /*delete*/
        else if(strcmp(token, "delete")==0)
        {   
            /*list, hashtable, bitmap 이름불러오기*/
            token = strtok(NULL, " ");
            /*list_delete*/
            if(list_names!=NULL)
            {  

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(token, list_names[i].name)==0)
                        {
                            list_delete(list_names[i].list);
                        }
                    }    
            }

            /*hashtable_delete*/
            else if(hash_names!=NULL)
            {
                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(token, hash_names[i].name)==0)
                        {
                            hash_destroy(hash_names[i].hash, remove_hash_elem);
                            break;
                        }
                    }

            }

            /*bitmap_delete*/
            else if(bitmap_names!=NULL)
            {
                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(token, bitmap_names[i].name)==0)
                        {
                            bitmap_destroy(bitmap_names[i].bitmap);
                            break;
                        }
                    } 

            }

        }

        /*dumpdata*/
        else if(strcmp(token, "dumpdata")==0)
        {
            token = strtok(NULL, " ");
            /*list_dumpdata*/
            if(list_names!=NULL)
            {
                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(token, list_names[i].name)==0)
                        {
                            list_dumpdata(list_names[i].list);
                        }
                    } 
                
            }

            /*hashtable_dumpdata*/
            else if(strcmp(token, "hashtable")==0)
            {
                char *name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);
                printf("%s", token);
                

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, hash_names[i].name)==0)
                        {
                            dump_hash(hash_names[i].hash);
                            break;
                        }
                    } 
            }

            /*bitmpa_dumpdata*/
            else if(bitmap_names!=NULL)
            {
                char *name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);
                

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            bitmap_print_binary((bitmap_names[i].bitmap));
                            break;

                        }
                    } 
            }

        }

        /*quit 구현*/
        else if(strcmp(token, "quit")==0) 
            exit(0);

        /*기타함수구현*/
        else
        {

              
            /*---------------list------------------*/
            if(strcmp(token, "list_push_back")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char* name = token;

                /*값 불러오기*/
                token = strtok(NULL, " ");
                int value = atoi(token);
                
                struct list_item *item = (struct list_item *)malloc(sizeof(struct list_item));
                item->data=value;

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {
                        list_push_back(list_names[i].list, item);
                        break;
                    }
                }
            }

            else if(strcmp(token, "list_push_front")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char* name = token;

                /*값 불러오기*/
                token = strtok(NULL, " ");
                int value = atoi(token);

                /*push할 list item 제작*/
                struct list_item *item = (struct list_item *)malloc(sizeof(struct list_item *));
                item->data=value;

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {
                        list_push_front(list_names[i].list, item);
                        break;
                    }
                }
            }

            else if(strcmp(token, "list_pop_front")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char* name = token;

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {
                        list_pop_front(list_names[i].list);
                        break;
                    }
                }
            }

            else if(strcmp(token, "list_pop_back")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char* name = token;

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {
                        list_pop_back(list_names[i].list);
                        break;
                    }
                }
            }

            else if(strcmp(token, "list_front")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");

                for(int i=0; i < counts; i++)
                {   
                    if(strcmp(token, list_names[i].name)==0)
                    {
                        struct list_elem * front = list_front(list_names[i].list);
                        struct list_item *front_item = list_entry(front, struct list_item, elem);
                        printf("%d\n", front_item->data);
                        break;
                    }
                }
            }


            else if(strcmp(token, "list_back")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");

                for(int i=0; i < counts; i++)
                {   
                    if(strcmp(token, list_names[i].name)==0)
                    {
                        struct list_elem * back = list_back(list_names[i].list);
                        struct list_item *back_item = list_entry(back, struct list_item, elem);
                        printf("%d\n", back_item->data);
                        break;
                    }
                }
            }

            else if(strcmp(token, "list_insert_ordered")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                /*값 불러오기*/
                token = strtok(NULL, " ");
                int value = atoi(token);
                
                struct list_item *item = (struct list_item *)malloc(sizeof(struct list_item));
                item->data=value;

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {
                        list_insert_ordered(list_names[i].list, item, list_less, (void *)"ascending");
                        break;
                    }
                }
            }

            else if(strcmp(token, "list_insert")==0){
                struct list_elem * before_elem;
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                /*before 값이 있는 list 구하기*/
                token = strtok(NULL, " ");
                int before = atoi(token);

                token = strtok(NULL, " ");
                int value = atoi(token);
                
                struct list_item *item = (struct list_item *)malloc(sizeof(struct list_item));
                item->data=value;

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {   
                        before_elem = list_begin(list_names[i].list);
                        for(int i=0; i<before; i++)
                            before_elem = list_next(before_elem);
                        
                        list_insert(before_elem, &item->elem);
                        break;
                    }
                }
            }

            else if(strcmp(token, "list_empty")==0){
                bool tf;
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {  
                        tf = list_empty(list_names[i].list);
                        printf(tf ? "true\n" : "false\n"); 
                    }
                }
            }

            else if(strcmp(token, "list_size")==0){
                size_t size;
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {  
                        size = list_size(list_names[i].list);
                        printf("%zu\n", size);
                    }
                }
            }

            else if(strcmp(token, "list_max")==0){
                struct list_elem * max;
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {  
                        max = list_max(list_names[i].list, list_less, "ascending");
                        printf("%d\n", list_entry(max, struct list_item, elem)->data);
                    }
                }
            }

            else if(strcmp(token, "list_min")==0){
                struct list_elem * min;
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {  
                        min = list_min(list_names[i].list, list_less, "ascending");
                        printf("%d\n", list_entry(min, struct list_item, elem)->data);
                    }
                }
            }

            else if(strcmp(token, "list_remove")==0){
                struct list_elem * remove;
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                int idx = atoi(token);

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {  
                        remove = list_begin(list_names[i].list);
                        for(int i=0; i<idx; i++)
                            remove = list_next(remove);
                        
                        list_remove(remove);
                        break;
                    }
                }
            }

            else if(strcmp(token, "list_reverse")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                        list_reverse(list_names[i].list);
                }
            }

            else if(strcmp(token, "list_shuffle")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                        list_shuffle(list_names[i].list);
                }
            }

            else if(strcmp(token, "list_sort")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                        list_sort(list_names[i].list,list_less, "ascending");
                }
            }

            else if(strcmp(token, "list_splice")==0){
                struct list_elem * before_elem;
                struct list_elem * first_elem;
                struct list_elem * second_elem;
                /*이름1 불러오기*/
                token = strtok(NULL, " ");
                char * before_name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(before_name,token);

                /*before 추출*/
                token = strtok(NULL, " ");
                int * before_idx = atoi(token);

                /*이름2 추출*/
                token = strtok(NULL, " ");
                char * after_name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(after_name,token);

                /*first 추출*/
                token = strtok(NULL, " ");
                int * first_idx = atoi(token);

                /*last 추출*/
                token = strtok(NULL, " ");
                int * last_idx = atoi(token);

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(before_name, list_names[i].name)==0)
                    {   
                        before_elem = list_begin(list_names[i].list);
                        for(int i=0; i<before_idx; i++)
                            before_elem = list_next(before_elem);
                    }

                }

                for(int i=0; i < counts; i++)
                {
                if(strcmp(after_name, list_names[i].name)==0)
                    {   
                        first_elem = list_begin(list_names[i].list);
                        for(int i=0; i<first_idx; i++)
                            first_elem = list_next(first_elem);
                        second_elem = list_begin(list_names[i].list);
                        for(int i=0; i<last_idx; i++)
                            second_elem = list_next(second_elem);
                    }
                }

                list_splice(before_elem, first_elem, second_elem);

                 
            }

            else if(strcmp(token, "list_swap")==0){
                struct list_elem * first_elem;
                struct list_elem * second_elem;
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);
                
                /*first_idx*/
                token = strtok(NULL, " ");
                int first_idx = atoi(token);

                /*second_idx*/
                token = strtok(NULL, " ");
                int second_idx = atoi(token);

                for(int i=0 ; i < counts ; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                    {   
                        first_elem = list_begin(list_names[i].list);
                        for(int j=0; j<first_idx; j++)
                            first_elem = list_next(first_elem);

                        second_elem = list_begin(list_names[i].list);
                        for(int k=0; k<second_idx; k++)
                            second_elem = list_next(second_elem);
                        break;
                    }
                }
                list_swap(first_elem, second_elem);
            }

            else if(strcmp(token, "list_unique")==0){
                /*이름 불러오기*/
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                struct list * tmp = list_create();
                token = strtok(NULL, " ");
                if(list_names==NULL)
                    list_names = (struct list_name *)malloc(sizeof(struct list_name)*100);
                
                list_names[counts].name = strdup(token);
                list_names[counts].list = tmp;
                counts++;

                for(int i=0; i < counts; i++)
                {
                    if(strcmp(name, list_names[i].name)==0)
                        list_unique(list_names[i].list,tmp,list_less,"ascending");
                }
            }
            /*---------------listend---------------*/

            /*---------------btimap---------------*/
            else if(strcmp(token, "bitmap_mark")==0)
            {
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t index = atoi(token);

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            bitmap_mark(bitmap_names[i].bitmap,index);
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_all")==0)
            {   
                bool tf;

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t start = atoi(token);

                token = strtok(NULL, " ");
                size_t cnt = atoi(token);


                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            tf = bitmap_all(bitmap_names[i].bitmap,start,cnt);
                            printf(tf ? "true\n" : "false\n");
                            break;
                        }         
                    } 
            }
        
            else if(strcmp(token, "bitmap_any")==0)
            {   
                bool tf;

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t start = atoi(token);

                token = strtok(NULL, " ");
                size_t cnt = atoi(token);


                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            tf = bitmap_any(bitmap_names[i].bitmap,start,cnt);
                            printf(tf ? "true\n" : "false\n");
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_contains")==0)
            {   
                bool tf;
                bool tf_input;

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t start = atoi(token);

                token = strtok(NULL, " ");
                size_t cnt = atoi(token);
                
                token = strtok(NULL, " ");
                if(!strcmp(token,"true"))
                    tf_input = 1;
                else
                    tf_input = 0;

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            tf = bitmap_contains(bitmap_names[i].bitmap,start,cnt, tf_input);
                            printf(tf ? "true\n" : "false\n");
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_count")==0)
            {   
                size_t num;
                bool tf_input;

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t start = atoi(token);

                token = strtok(NULL, " ");
                size_t cnt = atoi(token);
                
                token = strtok(NULL, " ");
                if(!strcmp(token,"true"))
                    tf_input = 1;
                else
                    tf_input = 0;

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            num = bitmap_count(bitmap_names[i].bitmap,start,cnt, tf_input);
                            printf("%zu\n",num);
                            break;
                        }         
                    } 
            }
        
            else if(strcmp(token, "bitmap_dump")==0)
            {
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            bitmap_dump(bitmap_names[i].bitmap);
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_expand")==0)
            {
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                int size = atoi(token);

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            bitmap_names[i].bitmap = bitmap_expand(bitmap_names[i].bitmap,size);
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_flip")==0)
            {
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t index = atoi(token);

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            bitmap_flip(bitmap_names[i].bitmap,index);
                            break;
                        }         
                    } 
            }
        
            else if(strcmp(token, "bitmap_none")==0)
            {   
                bool tf;

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t start = atoi(token);

                token = strtok(NULL, " ");
                size_t cnt = atoi(token);


                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            tf = bitmap_none(bitmap_names[i].bitmap,start,cnt);
                            printf(tf ? "true\n" : "false\n");
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_reset")==0)
            {
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t index = atoi(token);

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            bitmap_reset(bitmap_names[i].bitmap,index);
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_scan_and_flip")==0)
            {   
                int idx;
                bool tf_input;

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t start = atoi(token);

                token = strtok(NULL, " ");
                size_t cnt = atoi(token);
                
                token = strtok(NULL, " ");
                if(!strcmp(token,"true"))
                    tf_input = 1;
                else
                    tf_input = 0;

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            idx = bitmap_scan_and_flip(bitmap_names[i].bitmap, start, cnt, tf_input);
                            printf("%d\n", idx);
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_scan")==0)
            {   
                int idx;
                bool tf_input;

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t start = atoi(token);

                token = strtok(NULL, " ");
                size_t cnt = atoi(token);
                
                token = strtok(NULL, " ");
                if(!strcmp(token,"true"))
                    tf_input = 1;
                else
                    tf_input = 0;

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            idx = bitmap_scan(bitmap_names[i].bitmap, start, cnt, tf_input);
                            printf("%d\n", idx);
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_set_all")==0)
            {   
                bool tf_input;

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                if(!strcmp(token,"true"))
                    tf_input = 1;
                else
                    tf_input = 0;

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            bitmap_set_all(bitmap_names[i].bitmap, tf_input);
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_set_multiple")==0)
            {   
                int idx;
                bool tf_input;

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t start = atoi(token);

                token = strtok(NULL, " ");
                size_t cnt = atoi(token);
                
                token = strtok(NULL, " ");
                if(!strcmp(token,"true"))
                    tf_input = 1;
                else
                    tf_input = 0;

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            bitmap_set_multiple(bitmap_names[i].bitmap, start, cnt, tf_input);
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_set")==0)
            {   
                bool tf_input;

                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t  idx = atoi(token);

                token = strtok(NULL, " ");
                if(!strcmp(token,"true"))
                    tf_input = 1;
                else
                    tf_input = 0;

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            bitmap_set(bitmap_names[i].bitmap, idx, tf_input);
                            break;
                        }         
                    } 
            }

            else if(strcmp(token, "bitmap_size")==0)
            {   
                size_t size;
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            size = bitmap_size(bitmap_names[i].bitmap);
                            printf("%zu\n", size);
                            break;
                        }         
                    } 
            }       

            else if(strcmp(token, "bitmap_test")==0)
            {   
                bool tf;
                token = strtok(NULL, " ");
                char * name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);

                token = strtok(NULL, " ");
                size_t index = atoi(token);

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, bitmap_names[i].name)==0)
                        {
                            tf = bitmap_test(bitmap_names[i].bitmap,index);
                            if(tf)
                                printf("%s\n", "true");
                            else
                                printf("%s\n", "false");
                            break;
                        }         
                    } 
            }
            /*--------------bitmapend---------------*/

            /*--------------hashtable---------------*/
            else if(strcmp(token, "hash_insert")==0)
            {
                token = strtok(NULL, " ");
                char *name = (char*)malloc(sizeof(strlen(token))+1);
                strcpy(name,token);
                
                token = strtok(NULL, " ");
                int input_data = atoi(token);

                struct hash_elem *e = create_hash_elem(input_data);

                printf("%s %d\n", name,e->data);

                for(int i=0; i < counts; i++)
                    {
                        if(strcmp(name, hash_names[i].name)==0)
                        {
                            hash_insert (hash_names[i].hash , e);
                            break;
                        }
                    } 
            }
        
        }

    }   
}



