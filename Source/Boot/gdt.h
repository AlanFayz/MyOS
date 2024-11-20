#pragma once

#include <stdint.h>

// segment limit   - Specifies the size of the segment in memory. 
//                   If the granularity bit is 0, the limit is in bytes; if 1, the limit is in 4 KB blocks.

// segment address - Specifies the base address of the segment in memory.

// segment type    - Specifies the purpose of the segment and what operations are allowed on it.

// descriptor type - Specifies whether the segment is a system segment or a code/data segment.

// privilege level - Specifies the privilege level required to access the segment (0–3).

// present         - Indicates whether the segment is currently present in memory.

// granularity     - Controls the scaling of the segment limit.
//                   - 0: Limit is in bytes (fine-grained).
//                   - 1: Limit is in 4 KB blocks (coarse-grained, allows larger segments).

// size            - Specifies whether the segment operates in 16-bit or 32-bit mode.

// available       - This bit is typically unused but must be set to 0
//                   unless specifically required by the operating system.

// reserved        - Reserved bit that must always be set to 0.

typedef struct {
    uint16_t segment_limit_low;            
    uint16_t segment_address_low;          
    uint8_t  segment_address_middle;       
    uint8_t  segment_type : 4;             
    uint8_t  descriptor_type : 1;          
    uint8_t  descriptor_privilege_level : 2; 
    uint8_t  present : 1;                 
    uint8_t  segment_limit_high : 4;      
    uint8_t  available : 1;                
    uint8_t  reserved : 1;                 
    uint8_t  size : 1;                    
    uint8_t  granularity : 1;              
    uint8_t  segment_address_high;         
} __attribute__((packed)) gdt_descriptor_entry_t;

typedef struct {
    uint16_t limit;  
    uint32_t base;   
} __attribute__((packed)) gdt_descriptor_pointer_t;

typedef enum {
    SEGMENT_TYPE_DATA_READ_ONLY = 0,     
    SEGMENT_TYPE_DATA_READ_WRITE = 1,    
    SEGMENT_TYPE_CODE_EXECUTE_ONLY = 8,  
    SEGMENT_TYPE_CODE_EXECUTE_READ = 9   
} segment_type_t;

typedef enum {
    DESCRIPTOR_TYPE_SYSTEM = 0,          
    DESCRIPTOR_TYPE_CODE_DATA = 1        
} descriptor_type_t;

typedef enum {
    PRIVILEGE_LEVEL_RING_0 = 0,          // highest 
    PRIVILEGE_LEVEL_RING_1 = 1,          
    PRIVILEGE_LEVEL_RING_2 = 2,          
    PRIVILEGE_LEVEL_RING_3 = 3           // lowest 
} privilege_level_t;

typedef enum {
    SEGMENT_PRESENT_NO = 0,             
    SEGMENT_PRESENT_YES = 1             
} segment_present_t;

typedef enum {
    SEGMENT_SIZE_16_BIT = 0,            
    SEGMENT_SIZE_32_BIT = 1             
} SEGMENT_SIZE;

