#pragma once
#include "stdafx.h"
#include <iostream>
#include "func.h"

using namespace std;

namespace prune_and_search {

  using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для form2
	/// </summary>
	
	public ref class form2 : public System::Windows::Forms::Form
	{
	public:
	    int **Mat;
		int kolvo, h1;
		int kol;
	private: System::Windows::Forms::Button^  button1;
	public: 

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	public: form2(int **Matr, int a, int b)
		{
			InitializeComponent();
			Mat = Matr;
			kolvo = a;
			h1 = b;
			kol = 0;
			//
			//TODO: добавьте код конструктора
			//
			
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~form2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	protected: 
	private: System::Windows::Forms::Label^  label1;

	protected: 

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(form2::typeid));
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(26, 53);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(577, 249);
			this->richTextBox1->TabIndex = 0;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &form2::richTextBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 21.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label1->Location = System::Drawing::Point(167, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(321, 33);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Пошаговая сортировка";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(26, 317);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Начало";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &form2::button1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(413, 317);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Вперёд";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &form2::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(528, 317);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 5;
			this->button4->Text = L"Конец";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &form2::button4_Click);
			// 
			// form2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Wheat;
			this->ClientSize = System::Drawing::Size(637, 389);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->richTextBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"form2";
			this->Text = L"QuickSort";
			this->Load += gcnew System::EventHandler(this, &form2::form2_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void form2_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {

			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->richTextBox1->Text = L"";
				 kol = 0;
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(kol < kolvo)
			 {
				 this->richTextBox1->Text += L"Шаг "+ System::Convert::ToString(kol+1)+"\n";
				 for(int i = 0; i < h1; i++)
				 {
				     this->richTextBox1->Text += System::Convert::ToString(Mat[kol][i]);
					 if(i < (h1 - 1))
					 this->richTextBox1->Text += "   ";
				 }
				 this->richTextBox1->Text += "\n";
				 kol ++;
			 }
			 else
				 MessageBox::Show("Массив уже отсортирован.", "Ок", MessageBoxButtons::OK);
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->richTextBox1->Text = L"";
			 kol = kolvo;
			 for(int i = 0; i < kolvo; i++)
			 {
				 this->richTextBox1->Text += L"Шаг "+ System::Convert::ToString(i+1)+"\n";
				 for(int j = 0; j < h1; j ++)
				 {
					 this->richTextBox1->Text += System::Convert::ToString(Mat[i][j]);
					 if(j < (h1 - 1))
					     this->richTextBox1->Text += "   ";
				 }
				 this->richTextBox1->Text += "\n";
			 }
			 
		 }
};
}
