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
"""for i in range(1,12):
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

workbook.close()"""

"""L1 varied from 1kb to 256kb, l2 521 kb 8 way assoc"""

"""workbook1 = xlsxwriter.Workbook('Graph3.xlsx')
worksheet1 = workbook1.add_worksheet()

row=0
col=0
read_row=0

book=xlrd.open_workbook('cacti_table.xls')
first_sheet=book.sheet_by_index(0)
for i in range(1,10):
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
			
			string="./sim_cache 32 "+ str(int_size) + " " + str(item) + " 0 524288 8 gcc_trace.txt > temp.txt"
			print string 
			os.system("rm -f temp.txt")
			os.system(string)
			temp_file= open('temp.txt','r')
			for line in temp_file:
				if "combined L1+VC miss rate" in line:
					[int(s) for s in line.split() if s.isdigit()]
				if "L2 miss rate" in line:	
					[int(q) for q in line.split() if q.isdigit()]
					
					aat=htl[index]+(float(s)*(0.578177+(float(q)*mpt)))
					print aat
					
					worksheet1.write(row,col,int_size)
					worksheet1.write(row,col+1,item)
					worksheet1.write(row,col+2,s)
					worksheet1.write(row,col+3,q)
					worksheet1.write(row,col+4,str(htl[index]))
					worksheet1.write(row,col+5,str(aat))
					row +=1

	
		del l[-1]
		int_size=int_size*2
		temp_file.close()

workbook1.close()"""


"""L1 size varies, blocksize varies, assoc=4"""
"""

workbook = xlsxwriter.Workbook('Graph4.xlsx')
worksheet = workbook.add_worksheet()

row=0
col=0
read_row=0

book=xlrd.open_workbook('cacti_table1.xls')
first_sheet=book.sheet_by_index(0)
blocksize=[16,32,64,128]

for i in range(1,7):
		htl=[]

	
		htl.insert(0,round(first_sheet.cell(read_row,4).value,6))
		
		read_row +=1
		
		htl.insert(1,round(first_sheet.cell(read_row,4).value,6))
		read_row +=1
		htl.insert(2,round(first_sheet.cell(read_row,4).value,6))
		read_row +=1
		htl.insert(3,round(first_sheet.cell(read_row,4).value,6))
		read_row +=1
		
		print htl
		
		
		for index, item in enumerate(blocksize) :
			
			string="./sim_cache "+ str(item)+ " "+ str(int_size) + " 4 0 0 0 gcc_trace.txt > temp.txt"
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
					worksheet.write(row,col+2,str(s))
					row +=1

	
		
		int_size=int_size*2
		temp_file.close()

workbook.close()"""


"""L1 size varies, L2 size varies, assoc=4 for l1, assoc =8 for l2, blocksize=32"""



workbook1 = xlsxwriter.Workbook('Graph5.xlsx')
worksheet1 = workbook1.add_worksheet()
int_size=1024
row=0
col=0
read_row=0
read_row1=9

book=xlrd.open_workbook('cacti_table2.xls')
first_sheet=book.sheet_by_index(0)
for i in range(1,10):
		htl1=round(first_sheet.cell(read_row,4).value,6)
		read_row+=1
		print htl1
		for j in range(0,6):
			htl2=round(first_sheet.cell(read_row1+j,4).value,6)
			l2size=int(first_sheet.cell(read_row1+j,0).value)
			if(int_size<l2size):

					string="./sim_cache 32 "+ str(int_size) + " 4 0 "+str(l2size)+" 8 gcc_trace.txt > temp.txt"
					print string 
					os.system("rm -f temp.txt")
					os.system(string)
					temp_file= open('temp.txt','r')
					for line in temp_file:

		
	
						if "combined L1+VC miss rate" in line:
							[int(s) for s in line.split() if s.isdigit()]
						if "L2 miss rate" in line:	
							[int(q) for q in line.split() if q.isdigit()]
					
							aat=htl1+(float(s)*(htl2+(float(q)*mpt)))
							print aat
					
							worksheet1.write(row,col,int_size)
							worksheet1.write(row,col+1,l2size)
							worksheet1.write(row,col+2,s)
							worksheet1.write(row,col+3,q)
							worksheet1.write(row,col+4,str(htl1))
							worksheet1.write(row,col+5,str(htl2))
							worksheet1.write(row,col+6,str(aat))
							row +=1




		
	
			  
				
				

	
		
		int_size=int_size*2
		temp_file.close()

workbook1.close()


