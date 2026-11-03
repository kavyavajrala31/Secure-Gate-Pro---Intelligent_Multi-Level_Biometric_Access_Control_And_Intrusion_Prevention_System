#ifndef _R305_H_
#define _R305_H_
   
extern unsigned char collect(void);
extern unsigned char store(unsigned char);
extern unsigned char gen_template(unsigned int);
extern unsigned char enroll(unsigned int);
extern unsigned char delete_fp(unsigned int);
extern unsigned char deleteall_fp(void);
extern unsigned int identify_fp(void);
extern unsigned int search_fp(void);

#endif
