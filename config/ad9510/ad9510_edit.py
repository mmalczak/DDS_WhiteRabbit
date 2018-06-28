file_read = open("/home/milosz/Desktop/shared/ad9510_conf_internal.txt", "r")
file_write = open("/home/milosz/Desktop/shared/ad9510_conf_c_internal.txt", "w")

for line in file_read:
    file_write.write("spi_send_data("+"0x00"+line[1:3]+", 0x"+line[17:19]+", SPI_CS_AD9510_SEL);\n")

file_read = open("/home/milosz/Desktop/shared/ad9510_conf_external.txt", "r")
file_write = open("/home/milosz/Desktop/shared/ad9510_conf_c_external.txt", "w")

for line in file_read:
    file_write.write("spi_send_data("+"0x00"+line[1:3]+", 0x"+line[17:19]+", SPI_CS_AD9510_SEL);\n")
