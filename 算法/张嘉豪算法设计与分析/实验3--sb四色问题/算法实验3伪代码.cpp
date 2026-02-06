void DFS(int num)
	if num >n
		ans++
		return
	
	for i=1 to m
		color[num]=i	//涂色 
		if check(num)
			DFS(num+1)	//涂下一个点
		color[num]=0;	//回溯 
	
void DFS(int num)
	if num >n
		ans++
		return
	
	for i=1 to m
		if i==2 && num=1	//对称优化 
		break
		
		color[num]=i	//涂色 
		if check(num)
			DFS(num+1)	//涂下一个点
		color[num]=0;	//回溯 	

bool cmp(Node n1,Node n2)
	return n1.degree>n2.degree;
	
sort(Node+1,Node+num+1,cmp);	//按度数降序排序 
		
void one_DH(int num)
	if num >n
		cnt++
		return
	
	for i=1 to m	
		node[node[num].id].color=i;  
		if checkNode(num)
			DFS(num+1)	//涂下一个点
		node[node[num].id].color=0; 	//回溯 			
		
int MRV_find()	//找出可涂颜色数最少且没涂过颜色的点,返回下标
	for i to n
		if node[i].enableColor<min && color[node[i].id]==0
			min=node[i].enableColor
			index=color[node[i].id]
	return index;
		
void MRV(int num)
	if num >n
		cnt++
		return
	
	int c=MRV_find();
	if c==0
	return;
	for i=1 to m
		if checkNode(c,i)		//判断节点c能否涂颜色i
		color[Coloring_point]=i;//涂色 
		for j to n 
			if(matrix[c][j]==1)
		 		find (c) 		//找到邻接点现在的下标
			node[index].enableColor--
		
void MRV_DH(int num)
	if num >n
		cnt++
		return
	sort(Node+1,Node+num+1,cmp);//按度数降序排序 
	int c=MRV_find();			//找到可涂颜色数最少的点 
	if c==0
	return;
	for i=1 to m
		if checkNode(c,i)		//判断节点c能否涂颜色i
		color[Coloring_point]=i;//涂色 
		for j to n 
			if(matrix[c][j]==1)
		 		find (c) 		//找到邻接点现在的下标
		 	node[index].degree--; 
			node[index].enableColor--		

void MRV_DH_search(int num)
	if num >n
		cnt++
		return
	sort(Node+1,Node+num+1,cmp);//按度数降序排序 
	int c=MRV_find();			//找到可涂颜色数最少的点 
	if c==0
	return;
	for i=1 to m
		ifcheckNode(c,i)		//判断节点c能否涂颜色i
		color[Coloring_point]=i;//涂色 
		for j to n 
			if(matrix[c][j]==1)
		 		find (c) 		//找到邻接点现在的下标
		 	node[index].degree--; 
		 	if(checkNode(j,i))	//检查邻接点能否涂i 
				node[index].enableColor--
				if(node[index].enableColor==0)
					temp=j;		//记录不能涂色点的当前层数所在位置
					flag=0;		//判断涂色后邻接点是否能继续涂色
					break;
			if(flag==0)
				恢复+return 
			else
				color[Coloring_point]=i;
                MRV_DH_SEARCH(num+1);     //开始涂下一个点,即进入下一层
				回溯恢复	 


