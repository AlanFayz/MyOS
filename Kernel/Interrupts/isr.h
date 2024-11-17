//#pragma once
//
//
//#include "bool.h"
//
//
//typedef struct {
//    uint32_t gs;       
//    uint32_t fs;       
//    uint32_t es;       
//    uint32_t ds;       
//
//    uint32_t edi;      
//    uint32_t esi;      
//    uint32_t ebp;      
//    uint32_t esp;      //current stack pointer before ISR push
//
//    uint32_t ebx;      
//    uint32_t edx;      
//    uint32_t ecx;      
//    uint32_t eax;      
//
//    uint32_t int_no;   // interrupt number (vector)
//    uint32_t err_code; // error code (if present)
//
//    uint32_t eip;      // instruction pointer
//    uint32_t cs;       // code segment
//    uint32_t eflags;   // flags register
//
//    uint32_t esp_kern; // stack pointer in kernel mode (only for some interrupts)
//    uint32_t ss_kern;  // stack segment in kernel mode (only for some interrupts)          
//} interrupt_frame_t;
//
////interrupt service routines 
//
//#define ISR_DECLERATION_NO_ERROR_CODE(n) void isr##n(interrupt_frame_t* frame) __attribute__((interrupt))
//#define ISR_DECLERATION_ERROR_CODE(n)    void isr##n(interrupt_frame_t* frame, uint32_t error_code) __attribute__((interrupt))
//
//
//ISR_DECLERATION_NO_ERROR_CODE(0);
//ISR_DECLERATION_NO_ERROR_CODE(1);
//ISR_DECLERATION_NO_ERROR_CODE(2);
//ISR_DECLERATION_NO_ERROR_CODE(3);
//ISR_DECLERATION_NO_ERROR_CODE(4);
//ISR_DECLERATION_NO_ERROR_CODE(5);
//ISR_DECLERATION_NO_ERROR_CODE(6);
//ISR_DECLERATION_NO_ERROR_CODE(7);
//ISR_DECLERATION_ERROR_CODE(8);
//ISR_DECLERATION_NO_ERROR_CODE(9);
//ISR_DECLERATION_ERROR_CODE(10);
//ISR_DECLERATION_ERROR_CODE(11);
//ISR_DECLERATION_ERROR_CODE(12);
//ISR_DECLERATION_ERROR_CODE(13);
//ISR_DECLERATION_ERROR_CODE(14);
//ISR_DECLERATION_NO_ERROR_CODE(15);
//ISR_DECLERATION_NO_ERROR_CODE(16);
//ISR_DECLERATION_NO_ERROR_CODE(17);
//ISR_DECLERATION_NO_ERROR_CODE(18);
//ISR_DECLERATION_NO_ERROR_CODE(19);
//ISR_DECLERATION_NO_ERROR_CODE(20);
//ISR_DECLERATION_NO_ERROR_CODE(21);
//ISR_DECLERATION_NO_ERROR_CODE(22);
//ISR_DECLERATION_NO_ERROR_CODE(23);
//ISR_DECLERATION_NO_ERROR_CODE(24);
//ISR_DECLERATION_NO_ERROR_CODE(25);
//ISR_DECLERATION_NO_ERROR_CODE(26);
//ISR_DECLERATION_NO_ERROR_CODE(27);
//ISR_DECLERATION_NO_ERROR_CODE(28);
//ISR_DECLERATION_NO_ERROR_CODE(29);
//ISR_DECLERATION_NO_ERROR_CODE(30);
//ISR_DECLERATION_NO_ERROR_CODE(31);
//
////system calls
//ISR_DECLERATION_NO_ERROR_CODE(128);
//ISR_DECLERATION_NO_ERROR_CODE(177);
//
//
//void isr_common(interrupt_frame_t* frame, uint32_t error_code);
