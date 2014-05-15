/* GENERAL EVENTS */

#define NOTHING                                 0
#define PROCESSOR_CYCLES                        1
#define INSTRUCTIONS_COMPLETED                  2
#define MICRO_OPS_COMPLETED                     3
#define INSTRUCTIONS_FETCHED                    4
#define MICRO_OPS_DECODED                       5
#define PM_EVENT_TRANSITIONS                    6
#define PM_EVENT_CYCLES                         7

/* INSTRUCTION TYPES COMPLETED */

#define BRANCH_INSTRUCTIONS_COMPLETED           8
#define LOAD_MICRO_OPS_COMPLETED                9
#define STORE_MICRO_OPS_COMPLETED               10
#define NUMBER_OF_CQ_REDIRECTS                  11

/* BRANCH PREDICTION AND EXECUTION EVENTS */

#define BRANCHES_FINISHED                       12
#define TAKEN_BRANCHES_FINISHED                 13
#define FINISHED_UNCONDITIONAL_BRANCHES         14
#define BRANCHES_MISPREDICTED                   15
                                                  
//Branches in the BTB mispredicteddue to direction prediction.
#define BRANCHES_IN_BTB_MISPREDICTED            16            
#define BTB_HITS_AND_PSEUDO_HITS                17            
                                                              
/* PIPELINE STALLS */                                         
                                                              
#define CYCLES_DECODE_STALLED                   18            
#define CYCLES_ISSUE_STALLED                    19            
#define CYCLES_BRANCH_ISSUE_STALLED             20            
#define CYCLES_SFX0_SCHEDULE_STALLED            21            
#define CYCLES_SFX1_SCHEDULE_STALLED            22            
#define CYCLES_MU_SCHEDULE_STALLED              23            
#define CYCLES_LRU_SCHEDULE_STALLED             24            
#define CYCLES_BU_SCHEDULE_STALLED              25            
                                                              
/* Load/Store, Data Cache, and Data Line Fill Buffer (DLFB) Events */
                                                                     
#define TOTAL_TRANSLATED                        26                   
#define LOADS_TRANSLATED                        27                   
#define STORES_TRANSLATED                       28                   
#define TOUCHES_TRANSLATED                      29                   
#define CACHEOPS_TRANSLATED                     30            
#define CACHE_INHIBITED_ACCESSES_TRANSLATED     31                   
#define GUARDED_LOADS_TRANSLATED                32                   
#define WRITE_THROUGH_STORES_TRANSLATED         33                   
#define MISALIGNED_LOAD_STORE_ACCESS_TRANSLATED 34                   
#define TOTAL_ALLOCATED_TO_DLFB                 35                   
#define LOADS_TRANSLATED_ALLOCATED_TO_DLFB      36                   
#define STORES_COMPLETED_ALLOCATED_TO_DLFB      37                   
#define TOUCHES_COMPLETED_ALLOCATED_TO_DLFB     38                   
#define STORES_PERFORMED                        39                   
#define DATA_L1_CACHE_LOCKS                     40                   
#define DATA_L1_CACHE_RELOADS                   41                   
#define DATA_L1_CACHE_CASTOUTS                  42                   
                                                                     
/* Data Side Replay Conditions: Times Detected */                    
                                                                     
#define LOAD_MISS_WITH_DLFB_FULL                43                   
#define LOAD_MISS_WITH_LOAD_QUEUE_FULL          44                   
#define LOAD_GUARDED_MISS_WHEN_NOT_AT_BOT_OF_CQ 45                   
#define TRANSLATE_A_STORE_WHEN_QUEUE_IS_FULL    46                   
#define ADDRESS_COLLISION_TIMES_DETECTED        47                   
#define DATA_MMU_MISS_TIMES_DETECTED            48 
#define DATA_MMU_BUSY_TIMES_DETECTED            49                   
#define SECOND_PART_MISALIGN_ACCESS_TIMES_DTD   50            
                                                                     
/* Data Side Replay Conditions: Cycles Stalled */                    
                                                                     
#define LOAD_MISS_WITH_DLFB_FULL_CYCLES         51                   
#define LOAD_MISS_WITH_LOAD_QUEUE_FULL_CYCLES   52                   
#define LOAD_GUARDED_MISS_LOAD_NOT_BOT_OF_CQ    53                   
#define TRANSLATE_STORE_WHEN_STORE_Q_FULL       54                   
#define ADDRESS_COLLISION_CYCLES_DETECTED       55                   
#define DATA_MMU_MISS_CYCLES_DETECTED           56                   
#define DATA_MMU_BUSY_CYCLES_DETECTED           57                   
#define SND_PART_OF_MISALIGN_ACCESS_CYCLES_DTD  58                   
                                                                     
/* Fetch, Instruction Cache, Instruction Line Fill Buffer (ILFB), and Instruction */
                                                                                
#define INSTRUCTION_L1_CACHE_LOCKS              59                              
#define INSTRUCTION_L1_CACHE_RELOADS_FRM_FETCH  60                              
#define NUMBER_OF_FETCHES                       61                              
#define INSTRUCTION_MMU_TLB4K_RELOADS           62                              
#define INSTRUCTION_MMU_VSP_RELOADS             63                              
#define DATA_MMU_TLB4K_RELOADS                  64                              
#define DATA_MMU_VSP_RELOADS                    65     

#define L2MMU_MISSES                            66                              
                                                                                
/* BIU Interface Usage */                                                       
                                                                                
#define BIU_MASTER_REQUESTS                     67                              
#define BIU_MASTER_GLOBAL_REQUESTS              68                              
#define BIU_MASTER_DATA_SIDE_REQUESTS           69                              
#define BIU_NUMBER_OF_STASH_REQ_RECEIEVED       70                              
#define BIU_NUMBER_OF_STASH_ACCEPTS             71                              
                                                                                
/* Snoop */                                                                     
                                                                                
#define SNOOP_REQUESTS                          72                              
#define SNOOP_HITS                              73                              
#define SNOOP_PUSHES                            74                              
#define SNOOP_SHARING                           75                              
                                                                                
/* Threshold Events */                                                          
                                                                                
#define DATA_LINE_FILL_BUFFER_LOAD_MISS_CYCLES  76                              
#define ILFB_FETCH_MISS_CYCLES                  77                              
#define EXT_INP_INTERRUPT_LATENCY               78                              
#define CRITICAL_INP_INTERRUPT_LATENCY          79    

#define EXT_INP_INTERRUPT_PENDING_LATENCY       80                              
#define CRITICAL_INP_INTERRUPT_PENDING_LATENCY  81                              
                                                                                
/* Chaining Events */                                                           
                                                                                
#define PMC0_OVERFLOW                           82                              
#define PMC1_OVERFLOW                           83                              
#define PMC2_OVERFLOW                           84                              
#define PMC3_OVERFLOW                           85                              
                                                                                
/* Interrupt Events */                                                          
                                                                                
#define INTERRUPTS_TAKEN                        86                              
#define EXT_INP_INTERRUPTS_TAKEN                87                              
#define CRITICAL_INP_INTERRUPTS_TAKEN           88                              
#define SYSTEM_CALL_AND_TRAP_INTERRUPTS         89                              
                                                                                
/* Misc Events */                                                               
                                                                                
#define TRANSITIONS_TBL_BIT_SELECTED_BY_PMGC0   90                              
#define L2_LINEFILL_BUFFER                      91                              
#define L2_VS                                   92                              
#define CASTOUTS_RELEASED                       93      

#define INTV_ALLOCATIONS                        94                              
#define STORE_RETRIES_TO_MBAR                   95                              
#define STORE_RETRIES_DUE_TO_MISC               96                              
                                                                                
/* Stashing Events */                                                           
                                                                                
#define STASH_L1_HIT                            97                              
#define STASH_L2_HIT                            98                              
#define STASH_BUSY_1                            99                              
#define STASH_BUSY_2                            100                             
#define STASH_BUSY_3                            101                             
#define STASH_HIT                               102                             
#define STASH_HIT_DLFB                          103                             
#define STASH_REQUESTS                          106                             
#define STASHES_TO_L1_DATA_CACHE                107                             
#define STASHES_TO_BACKSIDE_L2                  108                             
#define STALLS_DUE_TO_NO_CAQ_OR_COB             109                             
                                                                                
/* Backside L2 Events */                                                        
                                                                                
#define L2_CACHE_ACCESSES                       110                             
#define L2_HIT_CACHE_ACCESSES                   111                             
#define L2_CACHE_DATA_ACCESSES                  112  
#define L2_CACHE_DATA_HITS                      113                             
#define L2_CACHE_INSTRUCTION_ACCESSES           114                             
#define L2_CACHE_INSTRUCTION_HITS               115                             
#define L2_CACHE_ALLOCATIONS                    116                             
#define L2_CACHE_DATA_ALLOCATIONS               117                             
#define L2_CACHE_DIRTY_DATA_ALLOCATIONS         118                             
#define L2_CACHE_INSTRUCTION_ALLOCATIONS        119                             
#define L2_CACHE_UPDATES                        120                             
#define L2_CACHE_CLEAN_UPDATES                  121                             
#define L2_CACHE_DIRTY_UPDATES                  122                             
#define L2_CACHE_CLEAN_REDUNDANT_UPDATES        123                             
#define L2_CACHE_DIRTY_REDUNDANT_UPDATES        124                             
#define L2_CACHE_LOCKS                          125                             
#define L2_CACHE_CASTOUTS                       126                             
#define L2_CACHE_DATA_DIRTY_HITS                127                             
#define INSTRUCTION_LFB_WENT_HIGH_PRIORITY      128                             
#define SNOOP_THROTTLING_TURNED_ON              129                             
#define L2_INVALIDATION_OF_CLEAN_LINES          130                             
#define L2_INVALIDATION_OF_INCOHERENT_LINES     131                             
#define L2_INVALIDATION_OF_COHERENT_LINE        132                             
#define COHERENT_LOOKUP_MISS_ADDR_MATCHES       133                             
                                                        
                                                                                
/* IAC, DAC Events */                                                           
                                                                                
#define IAC1S_DETECTED                          140                             
#define IAC2S_DETECTED                          141                             
#define DAC1S_DETECTED                          144                             
#define DAC2S_DETECTED                          145                             
                                                                                
                                                                                
/* DVT Events */                                                                
                                                                                
#define DVT0_DETECTED                           148                             
#define DVT1_DETECTED                           149                             
#define DVT2_DETECTED                           150                             
#define DVT3_DETECTED                           151                             
#define DVT4_DETECTED                           152                             
#define DVT5_DETECTED                           153                             
#define DVT6_DETECTED                           154                             
#define DVT7_DETECTED                           155                             
#define CYCLES_COMPLETION_STALLED_NEXUS         156                             
#define FPU_DOUBLE_PUMP                         160                             
#define FPU_FINISH                              161                             
#define FPU_DIVIDE_CYCLES                       162    

#define FPU_DENORM_INPUT                        163                             
#define FPU_RESULT_STALL                        164                             
#define FPU_FPSCR_FULL_STALL                    165                             
#define FPU_PIPE_SYNC_STALL                     166                             
#define FPU_INPUT_DATA_STALL                    167                             
                                                                                
/* Extended Load Store Events */                                                
                                                                                
#define DECORATED_LOADS                         176                             
#define DECORATED_STORES                        177                             
#define LOAD_RETRIES                            178                             
#define STWCX_SUCCESSFUL                        179                             
#define STWCX_UNSUCCESSFUL                      180                             
                                                       
