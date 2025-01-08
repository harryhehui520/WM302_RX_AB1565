#!/bin/python
import os
import sys

list_data = []

def InvertUint16(polyVal):
    tmp = 0
    for i in range(16):
        if polyVal & (1 << i):
            tmp |= 1 << (15 - i)
    return tmp

def App_Flash_Cal_Fw_Checksum(data):
    wCRCin = 0x0000
    wCPoly = 0x8005
    
    wCPoly = InvertUint16(wCPoly)

    for d in data:
        wCRCin ^= int(d, 16)
        for i in range(8):
            if wCRCin & 0x0001:
                wCRCin = (wCRCin >> 1) ^ wCPoly
            else:
                wCRCin >>= 1
    return wCRCin & 0xFFFF

def read_data_from_binary_file(filename, list_data):
    f = open(filename, 'rb')
    f.seek(0, 0)
    while True:
        t_byte = f.read(1)
        if len(t_byte) == 0:
            break
        else:
            list_data.append("0x%.2X" % ord(t_byte))

def write_data_to_text_file(filename, list_data):
    data_num_per_line_int = 32
    f_output = open(filename, 'w+')
    f_output.write('const unsigned char charge_case_bin_info[] = \n')
    f_output.write('{\n')
    f_output.write('    0x%.8x,    //Bld version(%d)\n' % (int(list_data[0xb8], 16), int(list_data[0xb8], 16)))
    f_output.write('    0x%.8x,    //App version(%d)\n' % (int(list_data[0xb9], 16), int(list_data[0xb9], 16)))
    f_output.write('    0x%.8x,    //Hw version(%d)\n' % (int(list_data[0xba], 16), int(list_data[0xba], 16)))
    f_output.write('    0x%.8x,    //File Size(%d)\n' % (len(list_data), len(list_data)))
    f_output.write('    0x%.8x,    //Checksum(%d)\n' % (App_Flash_Cal_Fw_Checksum(list_data), App_Flash_Cal_Fw_Checksum(list_data)))
    f_output.write('};\n')
    f_output.write('\n')
    f_output.write('\n')
    f_output.write('const unsigned char charge_case_bin_data[] = \n')
    f_output.write('{\n    ')
    if data_num_per_line_int > len(list_data):
        raise AssertionError("File size Invalid!")
    for i in range(0,len(list_data)):
        if ( (i != 0) and(i % data_num_per_line_int == 0)):
            f_output.write('\n    ')
            f_output.write(list_data[i]+', ')
        elif (i + 1) == len(list_data):
            f_output.write(list_data[i])
        else:
            f_output.write(list_data[i]+', ')
    f_output.write('\n};')
    f_output.close()
    print("File create success! File Size(%d) Checksum(%d) FW Version(%d.%d.%d)" % (len(list_data), App_Flash_Cal_Fw_Checksum(list_data), int(list_data[0xb8], 16), int(list_data[0xb9], 16), int(list_data[0xba], 16)))

def main():
    input_f = input("Please input source bin file:")
    output_f = input("Please input dest C file:")
    read_data_from_binary_file(input_f, list_data)
    write_data_to_text_file(output_f, list_data)

if __name__ == "__main__":
    sys.exit(main())