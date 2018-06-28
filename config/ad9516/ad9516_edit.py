file_read = open("/home/milosz/Desktop/shared/ad9516_conf.txt", "r")
file_write = open("/home/milosz/Desktop/shared/ad9516_conf_c.txt", "w")

for line in file_read:
    file_write.write("spi_send_data("+"0x"+line[1:5]+", 0x"+line[19:21]+", SPI_CS_AD9516_SEL);\n")