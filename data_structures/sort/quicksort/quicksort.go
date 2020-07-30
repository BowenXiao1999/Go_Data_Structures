package quicksort

// func QuickSortInts(arr *[]int) {
	
// 	l := 0
// 	r := len(*arr) - 1
	
// 	if len(*arr) < 2 {
// 		return
// 	}
// 	key := (*arr)[0]
// 	for l < r {
// 		for l < r && (*arr)[l] <= key {
// 			l++
// 		}
		
// 		for l < r && (*arr)[r] >= key {
// 			r--
// 		}

// 		if l < r {
// 			(*arr)[l], (*arr)[r] = (*arr)[r], (*arr)[l]
// 		}
// 	}

// 	(*arr)[l] = key
// 	QuickSortInts(&((*arr)[:l]))
// 	QuickSortInts(&((*arr)[l+1:]))
	
	
// }

func QuickSortInts(arr []int) {
	
	l := 0
	r := len(arr) - 1
	
	if len(arr) < 2 {
		return
	}
	key := arr[0]
	for l < r {
		for l < r && arr[l] <= key {
			l++
		}
		
		for l < r && arr[r] >= key {
			r--
		}

		if l < r {
			arr[l], arr[r] = arr[r], arr[l]
		}
	}

	arr[l] = key
	QuickSortInts(arr[:l])
	QuickSortInts(arr[l+1:])
	
	
}

