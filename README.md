# SoftTimer

使用链表创建了一个软件定时器, 理论上可以扩增至极大的数量.



## 如何使用 How to use?

1. 创建一个结构体, 用于定义软件定时器, 并对其通过api进行初始化, 用于设置指定的触发次数.

   ``` C
   //创建定时器结构体
   softTimer_t timer_1;
   //设定定时触发值
   softTimer_setup(&timer_1, 100);
   ```

   

2. 创建一个回调函数, 并将其注册进对应的软件定时器,用于在定时触发时,调用该回调函数.

   ``` C
   //创建回调函数
   void timer1Callback(){
       static int counter = 0;
       counter++;
       printf("timer1 update : %d\r\n", counter);
   }
   //将回调函数注册进指定的软件定时器
   softTimer_attach(&timer_1, timer1Callback);
   ```

   

3. 将定时器的tick节拍函数放置于一个稳定的定时中断之中.

   ``` C
   //假设此处的定时中断为1ms触发一次, 则前文创建的软件定时器1为每100ms触发一次.
   while(1){
           delay_ms(1);
           softTimer_tick();
   }
   ```



## 完整示例 example

``` C
#include <stdio.h>
#include "unistd.h"

#include "softTimer.h"

void timer1Callback(){
    static int counter = 0;
    counter++;
    printf("timer1 update : %d\r\n", counter);
}

void timer2Callback(){
    static int counter = 0;
    counter++;
    printf("timer2 update : %d\r\n", counter);
}

void timer3Callback(){
    static int counter = 0;
    counter++;
    printf("timer3 update : %d\r\n", counter);
}

int main() {
    softTimer_setup(&timer_1, 1);
    softTimer_setup(&timer_2, 2);
    softTimer_setup(&timer_3, 3);

    softTimer_attach(&timer_1, timer1Callback);
    softTimer_attach(&timer_2, timer2Callback);
    softTimer_attach(&timer_3, timer3Callback);

    while(1){
        sleep(1);	//定时时间为1s
        softTimer_tick();
    }

    return 0;
}
```



## 函数api解析

1. 初始化软件定时器

   ``` C
   void softTimer_setup(softTimer_t *target, int updateCount){
       target->updateCount = updateCount;	//写入更新时的节拍触发次数
       list_add(&target->node, &softTimer_Head);
   }
   ```

   

2. 注册回调函数

   ``` C
   void softTimer_attach(softTimer_t *target, void(*func)()){
       target->callBackFunction = func;	//注册回调函数
   }
   ```

   

3. 定时节拍函数

   ``` C
   void softTimer_tick(){
       softTimer_t *softTimer_ptr;	//创建一个软件定时器的结构体指针
   
       list_for_each_entry(softTimer_ptr, &softTimer_Head, node){	//正向遍历定时器链表, 依次更新计数值.
           softTimer_ptr->count++;
           if(softTimer_ptr->count == softTimer_ptr->updateCount){	//若触发更新数值, 则清零计数值并触发回调函数.
               softTimer_ptr->count = 0;
               softTimer_ptr->callBackFunction();
           }
       }
   }
   ```

   
