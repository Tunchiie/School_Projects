// CMSC 341 - Fall 2020 - Project 1
#include "csr.h"
#include <stdexcept>

CSR::CSR(){
    /***********************************
     *      To be implemented
     * ********************************/

  m_values = nullptr;
  
  m_col_index = nullptr;
  
  m_row_index = nullptr;
  
  m_nonzeros = 0;
  
  m_m = 0;
  
  m_n = 0;
  
  m_next = nullptr;
}

CSR::~CSR(){
    /***********************************
     *      To be implemented
     * ********************************/
  // clears all variables stored in class
  clear();
}


CSR::CSR(const CSR & rhs){
    /***********************************
     *      To be implemented
     * ********************************/
  
  m_nonzeros = rhs.m_nonzeros;
  
  m_m = rhs.m_m;

  m_n = rhs.m_n;

  m_next = nullptr;
  
  //checks if the list is empty
  if (m_m > 0 && m_n > 0){
    m_values = new int[m_nonzeros];
    m_col_index = new int[m_nonzeros];
    m_row_index = new int[m_m + 1];

    //populates row_index based on the number of rows + 1
    for (int i = 0; i < (m_m + 1); i++){
      
      m_row_index[i] = rhs.m_row_index[i];
    }

    /* populates col_index and values based on number
       of non zeros*/
    for (int i = 0; i < (m_nonzeros); i++){
      
      m_values[i] = rhs.m_values [i];
      m_col_index[i] = rhs.m_col_index[i];
      
    }
    
  }
  
  


}

void CSR::dump(){
    cout << endl;
    
    if (!empty()){
        for (int i=0;i<m_nonzeros;i++)
            cout << m_values[i] << " ";
        cout << endl;
        for (int i=0;i<m_nonzeros;i++)
            cout << m_col_index[i] << " ";
        cout << endl;
        for (int i=0;i<m_m+1;i++)
            cout << m_row_index[i] << " ";
    }
    else
        cout << "The object is empty!";
    cout << endl;
}

void CSR::clear(){
    /***********************************
     *      To be implemented
     * ********************************/
  if (!empty()){
    
    if (m_values != nullptr){
      delete [] m_values;
      m_values = nullptr;
    }
    
    
    if (m_col_index != nullptr){
      delete [] m_col_index;
      m_col_index = nullptr;
    }
    
    
    if (m_row_index != nullptr){
      delete [] m_row_index;
      m_row_index = nullptr;
    }
    
    
    if (m_next != nullptr){
      m_next = nullptr;
    }
  }
  
  m_nonzeros = 0;
  
  m_m = 0;
  
  m_n = 0;

  
}

bool CSR::empty() const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
  bool empty = false;

  //checks if columns and row are empty
  if ((m_n == 0) && (m_m == 0)){
    empty = true;
    return empty;
  }
  return empty;
}

void CSR::compress(int m, int n, int array[], int arraySize){
    /***********************************
     *      To be implemented
     * ********************************/
  int numArray = 0, columnPos = 0;
  int rowPos = 0, counter = 0;
  
  m_m = m;
  
  m_n = n;

  // checks if incoming array is empty
  if (arraySize > 0){
    
    m_row_index = new int[m_m + 1];

    //populates row_index
    for (int i = 0; i < (m_m + 1); i++){
      
      if (i == 0){
	
	m_row_index[rowPos++] = 0;
	
      }
      
      else{
	
      m_row_index[rowPos++] = m_nonzeros;
      
      }
      
      if (counter != arraySize){
	// counts the non zero numbers
	for (int j = 0; j < m_n; j++){
	
	  if (array[counter] != 0){
	    
	    m_nonzeros++;
	    	    
	  }
	  
	  counter++;
	   
	}	
	
      }
    }

    //checks if there are non zero numbers
    if (m_nonzeros > 0){
      
      m_values = new int[m_nonzeros];
      
      m_col_index = new int[m_nonzeros];
      
      counter = 0;
      
      //using the number of non zero numbers
      //col_index and values are populated
      for (int i = 0; i < (m_m + 1); i++){
	
	if (counter != arraySize){
	  
	  for (int j = 0; j < m_n; j++){
	    
	    if (array[counter] != 0){
	    
	      m_values[numArray++] = array[counter];
	      m_col_index[columnPos++] = j;
	      
	    }
	    counter++; 
	  }
	  
	}
      }
    }
  }
 
}

      
int CSR::getAt(int row, int  col) const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

  
  // checks if row and column asked for are in range
  if (row < 0 || col < 0){
    throw runtime_error("matrix is not that small");
  }
  else if (row > m_m || col > m_n){
    throw runtime_error("matrix is not that large");
  }
  else{
    int row_start = m_row_index[row];
    int row_end = m_row_index[row + 1];

    //goes through matrix until it gets the wanted value
    for (int i = row_start; i < row_end; i++){
      if (m_col_index[i] == col){
	return m_values[i];
      }
    }
    return  0;
  }
}


bool CSR::operator==(const CSR & rhs) const{
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
  
     * ********************************/

  bool numOfNonZeros = false, numOfColumns = false;
  bool sameColumn = false;
  bool numOfRows = false, sameRow = false;
  int sameRowIndex = 0, sameValuesIndex = 0;
  
  
  // checks if two matrices are exact copies of each other
  if (rhs.m_m != 0 && m_m != 0){

    // checks for number of zeros
    if (m_nonzeros == rhs.m_nonzeros){
      numOfNonZeros= true;
    }

    // checks for number of columns
    if (m_n == rhs.m_n){
      numOfColumns = true;
    }

    //checks for number of rows
    if (m_m == rhs.m_m){
      numOfRows = true;
    }

    //checks if the matrices have the non xero numbers at
    //          exactly the same rows
    if (m_m == rhs.m_m){
      
      for (int i = 0; i < (rhs.m_m + 1); i++){

	if (m_row_index[i] == rhs.m_row_index[i]){
	  
	  sameRowIndex++;
	}
	
	if (sameRowIndex == (m_m + 1)){
	  sameRow = true;
	}
      }
    }

    //checks if the matrices have the non xero numbers at
    //          exactly the same position
    if (m_nonzeros == rhs.m_nonzeros){
      if (m_values != nullptr && m_col_index != nullptr){
	
	for (int i = 0; i < (rhs.m_nonzeros); i++){
	  
	  if (m_values[i] == rhs.m_values [i] &&	\
	      m_col_index[i] == rhs.m_col_index[i]){
	    
	    sameValuesIndex++;
	  }
	  
	}
      }
      if (sameValuesIndex == (m_nonzeros)){
	sameColumn = true;
      }
    }
  }
  
  else{
    cout << "This is an empty matrix" << endl;
  }

  //if all rows and columns are the same, the matrices are
  //                                      copies
  if ((sameColumn == true) && (sameRow == true)			\
      && (numOfNonZeros == true) && (numOfColumns == true)	\
      && (numOfRows == true)){
    
    return true;
  }

  return false;
}
  


int CSR::sparseRatio(){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/

  //gets the ratio of zeros to non zero numbers
  double noOfZeros = (m_n * m_m) - m_nonzeros;
  double noOfItems = m_m * m_n;
  double ratio = noOfZeros / noOfItems;
  
  return (ratio * 100);
}


