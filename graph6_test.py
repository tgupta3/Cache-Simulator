import os
import math
import xlsxwriter
import xlrd

workbook = xlsxwriter.Workbook('Graph5.xlsx')
worksheet = workbook.add_worksheet()

row=0
col=0


int_size=1024
l=[1,2,4,8]
print l
mpt=20.2
read_row=0
read_col=4
book=xlrd.open_workbook('cacti_table3.xls')
first_sheet=book.sheet_by_index(0)
second_sheet=book.sheet_by_index(1)
print first_sheet.cell(1,4)
victim_cache=[0,2,4,8,16]
assoc=[1,2,4]
for index1,t in enumerate(assoc) :
	int_size=1024
	
	for i in range(1,7):
		htl=round(first_sheet.cell(read_row,4).value,6)
		read_row +=1
		for index, item in enumerate(victim_cache) :
			
			vht=[]
			vht=[0,0.131305,0.131305,0.135715,0.142543]
			string="./sim_cache 32 "+ str(int_size) + " " + str(t) + " " + str(item) + " 65536 8 gcc_trace.txt > temp.txt"
			print string 
			os.system("rm -f temp.txt")
			os.system(string)
			temp_file= open('temp.txt','r')
			for line in temp_file:
				
				if "combined L1+VC miss rate" in line:
						[int(s) for s in line.split() if s.isdigit()]

				if "swap request rate" in line:
						[int (w) for w in line.split() if w.isdigit()]


				if "L2 miss rate" in line:	
						[int(q) for q in line.split() if q.isdigit()]

				
				

						aat=htl+ (float(w)*vht[index]) +(float(s)*(0.341213+(float(q)*mpt)))
						print aat
					
						worksheet.write(row,col,int_size)
						worksheet.write(row,col+1,item)
						worksheet.write(row,col+2,s)
						worksheet.write(row,col+3,q)
						worksheet.write(row,col+4,w)
						worksheet.write(row,col+5,t)
					
						worksheet.write(row,col+6,str(htl))
						worksheet.write(row,col+7,str(aat))
						row +=1

	
		
		int_size=int_size*2
		temp_file.close()

workbook.close()

