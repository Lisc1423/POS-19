#ifndef __imitate_spi_H
#define __imitate_spi_H
#ifdef __cplusplus
 extern "C" {
#endif

void ispi1_write_read(uint8_t* writeBuffer, uint8_t* readBuffer, int len);  
void ispi3_write_read(uint8_t* writeBuffer, uint8_t* readBuffer, int len);
   
   
#ifdef __cplusplus
}
#endif
#endif