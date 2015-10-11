import os
import math
import xlsxwriter
import xlrd

workbook = xlsxwriter.Workbook('Graph1.xlsx')
worksheet = workbook.add_worksheet()

row=0
col=0


int_size=1024
l=[1,2,4,8]
print l
mpt=20.2
read_row=0
read_col=4
book=xlrd.open_workbook('cacti_table.xls')
first_sheet=book.sheet_by_index(0)
print first_sheet.cell(1,4)
for i in range(1,12):
		htl=[]
		htl.insert(0,round(first_sheet.cell(read_row,4).value,6))
		
		read_row +=1
		
		htl.insert(1,round(first_sheet.cell(read_row,4).value,6))
		read_row +=1
		htl.insert(2,round(first_sheet.cell(read_row,4).value,6))
		read_row +=1
		htl.insert(3,round(first_sheet.cell(read_row,4).value,6))
		read_row +=1
		htl.insert(4,round(first_sheet.cell(read_row,4).value,6))
		read_row +=1
		print htl
		
		l.insert(4,int(int_size/32))
		print l	
	
		for index, item in enumerate(l) :
			
			string="./sim_cache 32 "+ str(int_size) + " " + str(item) + " 0 0 0 gcc_trace.txt > temp.txt"
			print string 
			os.system("rm -f temp.txt")
			os.system(string)
			temp_file= open('temp.txt','r')
			for line in temp_file:
				if "combined L1+VC miss rate" in line:
					[int(s) for s in line.split() if s.isdigit()]
					aat=htl[index]+(float(s)*mpt)
					print aat
					
					worksheet.write(row,col,int_size)
					worksheet.write(row,col+1,item)
					worksheet.write(row,col+2,s)
					worksheet.write(row,col+3,str(htl[index]))
					worksheet.write(row,col+4,str(aat))
					row +=1

	
		del l[-1]
		int_size=int_size*2
		temp_file.close()

workbook.close()




