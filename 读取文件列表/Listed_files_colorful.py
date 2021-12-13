import os

def Size_Convert(size):
	
	KB, MB, GB = 1024, 1024**2, 1024**3
	if size >= GB:
		return str(size/GB)+'G Bytes'
	elif size >= MB:
		return str(size/MB)+'M Bytes'
	elif size >= KB:
		return str(size/KB)+'K Bytes'
	else:
		return str(size)+'Bytes'	


def Counter_classify(level):
	counter = 0
	while counter < level:
		strd = "\033[" + str(counter+31) + "m"
		print(strd+'---'+"\033[0m",end='')
		counter+=1


def Dir_visit(path,cur_dir_level):
	
	cur_size = 0 #当前文件大小

	
	for lists in os.listdir(path):
		
 		#拼接路径
		sub_path = os.path.join(path, lists)
		
		Counter_classify(cur_dir_level)
		print("\033[36m"+"< " +lists+ " >" +"\033[0m")
		
		if os.path.isfile(sub_path):
			
			Counter_classify(cur_dir_level)
			print("\033[37m"+"文件大小为:" + Size_Convert(os.path.getsize(sub_path)) + "\033[0m")
			cur_size += os.path.getsize(sub_path)
			
		elif os.path.isdir(sub_path):
			Counter_classify(cur_dir_level)
			print("\033[32m"+"开始展示文件夹"+ "< " +lists+ " >"+"的内容:"+ "\033[0m")
			dir_size = os.path.getsize(sub_path)+Dir_visit(sub_path,cur_dir_level+1)
			
			Counter_classify(cur_dir_level)
			print("\033[32m"+"文件夹"+"< " +lists+ " >"+"展示完毕,此文件夹的总大小为:"+Size_Convert(dir_size)+ "\033[0m")
			cur_size += dir_size
			
	return cur_size
	
def judge_path(path):
	if not os.path.isdir(path):
		print('Error:"', path, '" is not a directory or does not exist.')
		return
	print("开始展示该文件夹的内容:")
	dir_size = os.path.getsize(path)+Dir_visit(path,1)
	print("展示完毕,此文件夹的总大小为:"+Size_Convert(dir_size))
	
if __name__=='__main__':
	
	#path = r'D:\project\github\mygit'
	path = input("请输入文件夹绝对路径:\n")
	judge_path(path)
	os.system("pause")
	
	
