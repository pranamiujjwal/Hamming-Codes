#include<iostream>
#include<cstdlib>
class MultipleParityCheck{
  private:
    int size;
    bool *matrix;

  public:
    MultipleParityCheck(int size){
			this->size = size;
			matrix = new bool[size*size];
    }

		void showMatrix(){
			for(int i=0;i<size*size;i++){
				if(i%size==0) std::cout<<std::endl;
				std::cout<<matrix[i]<<" ";
			}
			std::cout<<std::endl;
		}

		void fillRandom(){
			for(int i=1;i<size*size;i++){
				matrix[i] = rand()%2;
			}
			int parity = 1;
			while(parity<=size/2){
				matrix[parity] = 0;
				matrix[parity*size] = 0;
				parity *= 2;
			}
		}

		void parityCheck(){
			int parity = 1;
			while(parity<=size/2){
				int count_col = 0;
				int count_row = 0;
				std::cout<<"\nCol: ";
				for(int col=parity; col<size; col+=(parity+parity)){
					for(int couple=0; couple<parity; couple++){
						std::cout<<col+couple<<"+";
						for(int row=0; row<size; row++){
							if(matrix[size*row+col+couple])  count_col++;
						}
					}
				}
				std::cout<<":\tSumTotal="<<count_col;
				if(count_col%2!=0){
					matrix[parity] = 1;
					std::cout<<"[odd]->Changing paraity at: "<<parity<<std::endl;
				}
				std::cout<<"\nRow: ";
				for(int row=parity; row<size; row+=(parity+parity)){
					for(int couple=0; couple<parity; couple++){
						std::cout<<(row+couple)*size<<"+";
						for(int col=0; col<size; col++){
							if(matrix[size*(row+couple)+col])  count_row++;
						}
					}
				}
				std::cout<<":\tSumTotal="<<count_row;
				if(count_row%2!=0){
					matrix[parity*size] = 1;
					std::cout<<"[odd]->Changing paraity at: "<<parity*size<<std::endl;
				}
				parity *= 2;
			}
			int count = 0;
			for(int idx=0; idx<size*size; idx++){
				if(matrix[idx]) count++;
			}
			if(count%2!=0){
				matrix[0] = 1;
				std::cout<<"Parity "<<0<<"[odd]->Changing paraity at: "<<0<<std::endl;
			}
		}

		void insertError(int idx){
			matrix[idx] = !matrix[idx];
		}

		void detectError(){
			int error_row[size]={0};
			int error_col[size]={0};
			int parity = 1;
			while(parity<=size/2){
				int count_col = 0;
				int count_row = 0;
				std::cout<<"\nChecking Col: ";
				for(int col=parity; col<size; col+=(parity+parity)){
					for(int couple=0; couple<parity; couple++){
						std::cout<<col+couple<<"+";
						for(int row=0; row<size; row++){
							if(matrix[size*row+col+couple])  count_col++;
						}
					}
				}
				if(matrix[parity]) count_col--;
				std::cout<<":\tSumTotal="<<count_col;
				if(count_col%2!=0){
					if(!matrix[parity]){
						for(int col=parity; col<size; col+=(parity+parity)){
							for(int couple=0; couple<parity; couple++){
								error_col[col+couple]++;
							}
						}
						std::cout<<"[odd], parity=0, !!Error at this grp";
					}
				}else if(matrix[parity]){
					for(int col=parity; col<size; col+=(parity+parity)){
						for(int couple=0; couple<parity; couple++){
							error_col[col+couple]++;
						}
					}
					std::cout<<"[even], parity=1, !!Error at this grp";
				}

				std::cout<<"\nChecking Row: ";
				for(int row=parity; row<size; row+=(parity+parity)){
					for(int couple=0; couple<parity; couple++){
						std::cout<<(row+couple)*size<<"+";
						for(int col=0; col<size; col++){
							if(matrix[size*(row+couple)+col])  count_row++;
						}
					}
				}
				if(matrix[parity*size]) count_row--;
				std::cout<<":\tSumTotal="<<count_row;
				if(count_row%2!=0){
					if(!matrix[parity*size]){
						for(int row=parity; row<size; row+=(parity+parity)){
							for(int couple=0; couple<parity; couple++){
								error_row[row+couple]++;
							}
						}
						std::cout<<"[odd], parity=0, !!Error at this grp\n";
					}
				}else if(matrix[parity*size]){
					for(int row=parity; row<size; row+=(parity+parity)){
						for(int couple=0; couple<parity; couple++){
							error_row[row+couple]++;
						}
					}
					std::cout<<"[even], parity=1, !!Error at this grp\n";
				}
				parity *= 2;
			}
			std::cout<<"\nError Col: ";
			for(int i=0; i<size; i++){
				std::cout<<error_col[i]<<"  ";
			}
			std::cout<<"\nError Row: ";
			for(int i=0; i<size; i++){
				std::cout<<error_row[i]<<"  ";
			}
			std::cout<<std::endl;
		}
};

int main(){
	MultipleParityCheck mpc(4);
	mpc.fillRandom();
	mpc.parityCheck();
	mpc.showMatrix();
	mpc.insertError(7);
	mpc.showMatrix();
	mpc.detectError();
	return 0;
}