#include <iostream>
#include <omp.h>
using namespace std;

#define BUFFER_SIZE 5
#define NUM_ITEMS 10
int buffer[BUFFER_SIZE];
int countItems = 0;
int in = 0;
int out = 0;

int main(){

    omp_set_num_threads(2);
    #pragma omp parallel sections
    {
        //Producer section
        #pragma omp section
        {
            for(int i = 1;i<= NUM_ITEMS; i++){
                int producedItem = i;

                bool not_produced = true;
                while(not_produced){
                    #pragma omp critical
                    {
                        if(countItems < BUFFER_SIZE){
                            buffer[in] = producedItem;
                            in = (in + 1) % BUFFER_SIZE;
                            countItems++;
                            cout<<"Producer Produced item" << producedItem<<"| Buffer Count = "<<countItems<<endl;
                            not_produced = false;
                        }
                    }
                }
            }
        }

        //Consumer Section
        #pragma omp section
        {
            for(int i = 1;i<= NUM_ITEMS;i++){
                int consumedItem;
                bool not_consumed = true;

                while(not_consumed){
                    #pragma omp critical
                    {
                        if(countItems > 0){
                            consumedItem = buffer[out];
                            out = (out + 1) % BUFFER_SIZE;
                            countItems--;
                            cout<<"Consumer Consumed item" << consumedItem<<"| Buffer Count = "<<countItems<<endl;
                            not_consumed = false;
                        }
                    }
                }
            }
        }
    }
    return 0;

}