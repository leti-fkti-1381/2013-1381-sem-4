#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctime>    
#include "stdlib.h"
#include "form2.h"
using namespace std;
int *d = NULL;
int h1 = 0;
int A = 0,B = 0,i = 0;
int from ,to ;
int **Matr = NULL;
int kolvo1 = 0;
bool f = true; // Проверка на предотвращение повторной генерации.
bool p = false; // Проверка на сгенерированый массив,если он сгенерирован, то можно сортировать
bool c = true; // Проверка на повторное чтение с файла
bool w = true; // Проверка на отсортированный массив,если отсортирован, то больше не сортирует
bool de = true;// Проверка на сгенерированный массив, который уже есть в текстбоксе.Если он есть, то вывод сообщения о просьбе удалить массив,а потом считывать.
char *filename1 = NULL;
char *filename2 = NULL;
long int search_time;
time_t time( time_t * timeptr );
namespace prune_and_search {

  using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
    using namespace System::Runtime::InteropServices;
	using namespace System::IO;

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::Label^  label1;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;
	private: System::Windows::Forms::Label^  label5;

	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;

	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::Button^  button6;

	private: System::ComponentModel::IContainer^  components;




	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 27.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label1->Location = System::Drawing::Point(357, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(298, 43);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Prune and Search";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(456, 141);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(27, 18);
			this->label2->TabIndex = 4;
			this->label2->Text = L"от";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(601, 141);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(22, 18);
			this->label3->TabIndex = 5;
			this->label3->Text = L"до";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 14.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label4->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label4->Location = System::Drawing::Point(484, 96);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(236, 22);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Диапазон генерации чисел";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(743, 353);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(251, 34);
			this->button1->TabIndex = 7;
			this->button1->Text = L"Сгенерировать массив";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(743, 250);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(251, 34);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Отсортировать массив";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button3->Location = System::Drawing::Point(475, 353);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(245, 34);
			this->button3->TabIndex = 10;
			this->button3->Text = L"Сохранить в файл";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button4->Location = System::Drawing::Point(475, 407);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(246, 34);
			this->button4->TabIndex = 11;
			this->button4->Text = L"Чтение из файла";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(509, 178);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(105, 16);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Размер массива:";
			this->label5->Click += gcnew System::EventHandler(this, &Form1::label5_Click);
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button5->Location = System::Drawing::Point(743, 407);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(251, 34);
			this->button5->TabIndex = 14;
			this->button5->Text = L"Удалить массив";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 98);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(438, 146);
			this->textBox1->TabIndex = 15;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(489, 141);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(106, 20);
			this->textBox2->TabIndex = 16;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(629, 141);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(106, 20);
			this->textBox3->TabIndex = 17;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Form1::textBox3_TextChanged);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(629, 176);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(106, 20);
			this->textBox4->TabIndex = 18;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &Form1::textBox4_TextChanged);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(918, 152);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(62, 20);
			this->textBox5->TabIndex = 19;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(753, 156);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(129, 16);
			this->label6->TabIndex = 20;
			this->label6->Text = L"Время(сортировки):";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(915, 73);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(79, 14);
			this->label7->TabIndex = 21;
			this->label7->Text = L"миллисекунды";
			this->label7->Click += gcnew System::EventHandler(this, &Form1::label7_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(765, 96);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(117, 16);
			this->label8->TabIndex = 22;
			this->label8->Text = L"Время(генерации):";
			this->label8->Click += gcnew System::EventHandler(this, &Form1::label8_Click);
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(918, 98);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(62, 20);
			this->textBox6->TabIndex = 23;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label9->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label9->Location = System::Drawing::Point(24, 73);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(188, 19);
			this->label9->TabIndex = 24;
			this->label9->Text = L"Сгенерированный массив";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(12, 295);
			this->textBox7->Multiline = true;
			this->textBox7->Name = L"textBox7";
			this->textBox7->ReadOnly = true;
			this->textBox7->Size = System::Drawing::Size(438, 146);
			this->textBox7->TabIndex = 25;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label10->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->label10->Location = System::Drawing::Point(24, 273);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(199, 19);
			this->label10->TabIndex = 26;
			this->label10->Text = L"Отсортированный массив";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(648, 212);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(269, 16);
			this->label11->TabIndex = 27;
			this->label11->Text = L"Время библиотечной функции(сортировки):";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(918, 210);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(62, 20);
			this->textBox8->TabIndex = 28;
			this->textBox8->TextChanged += gcnew System::EventHandler(this, &Form1::textBox8_TextChanged);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->checkBox1->Location = System::Drawing::Point(564, 258);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->checkBox1->Size = System::Drawing::Size(156, 20);
			this->checkBox1->TabIndex = 30;
			this->checkBox1->Text = L"Выполнить пошагово";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBox1_CheckedChanged);
			// 
			// button6
			// 
			this->button6->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button6->Location = System::Drawing::Point(743, 295);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(251, 34);
			this->button6->TabIndex = 31;
			this->button6->Text = L"Отсортировать массив библ.функцией";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 14);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Wheat;
			this->ClientSize = System::Drawing::Size(1006, 453);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Font = (gcnew System::Drawing::Font(L"Times New Roman", 8.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)), 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"Quick Sort";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
	}
//Кнопка сортировки массива
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		if(w == true)
		 {
			 if (p == true)
			 {
			 f = false;
			 time_t start,end;
			 w = false;
			 // Тут вставить новую формочку в которую будем выводить пошаговую сортировку.
			 if(checkBox1->Checked == true)
			 {
				//MessageBox::Show("Выбрана пошаговая сортировка","Ок",  MessageBoxButtons::OK);

				 //Вызываем форму 2
				 time(&start);
				 for(i = 0; i < kolvo1; i ++)
					 free(Matr[i]);
				 free(Matr);
				 Matr = NULL;
				 kolvo1 = 0;
				 sort_s_vizual(d, 0, h1-1);
				 Form ^frm2 = gcnew form2(Matr, kolvo1, h1);
				 frm2->Show();
			 }
			 else
			 {
				            time(&start);
				            sort(d, 0, h1-1);
			 	   		    for (i = 0; i < h1; i++)
							   {
					                textBox7->Text += System::Convert::ToString(d[i]);
									if(i < (h1 - 1))
										textBox7->Text += "   ";
							   }
			 }
				 time(&end);
				 search_time = long int (end-start);
				 textBox5->Text += System::Convert::ToString(search_time);
			 }
			 else
			 MessageBox::Show("Массив был удален или не создан.\nСгенерируйте новый массив!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else
		   MessageBox::Show("Массив был отсортирован.\nСгенерируйте новый массив.", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		 }
// Кнопка очистки массива
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 f = true;
			 p = false;
			 c = true;
			 w = true;
			 de = true;
			 textBox1->Clear();
			 textBox2->Clear();
			 textBox3->Clear();
			 textBox4->Clear();
			 textBox5->Clear();
			 textBox6->Clear();
			 textBox7->Clear();
			 textBox8->Clear();
			 A = 0;
			 B = 0;
			 h1 = 0;
			 delete d;
			 this->textBox4->ReadOnly = false;
		 }
// Устанавливаем нижнюю границу
  private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			    String^ t = this->textBox2->Text;
				char *str1 = (char*)(void*)Marshal::StringToHGlobalAnsi(t);
				string r = (string)(str1);
				A = atoi(r.c_str());
		   }
//Устанавливаем верхнюю границу
private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			    String^ t = this->textBox3->Text;
				char *str1 = (char*)(void*)Marshal::StringToHGlobalAnsi(t);
				string r = (string)(str1);
				B = atoi(r.c_str());
		 }
//Задаем размер массива
private: System::Void textBox4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			    String^ t = this->textBox4->Text;
				char *str1 = (char*)(void*)Marshal::StringToHGlobalAnsi(t);
				string r = (string)(str1);
				h1 = atoi(r.c_str());
         }
// Кнопка генерации массива
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		if(f == true)
		{
             if( A >= B)
				 MessageBox::Show("Некорректно заданы границы генерации", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
			 else
			 {
				 if( h1 <= 0 )
					 MessageBox::Show("Массив не может быть сгенерирован.\nВведите корректный размер массива", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				 else
				 {
					 f = false;
					 p = true;
					 de = false;
					 time_t start,end;
					 time(&start);
					 d = Generation(h1, A, B);
						       for (i = 0; i < h1; i++)
							   {
					                textBox1->Text += System::Convert::ToString(d[i]);
									if(i < (h1 - 1))
										textBox1->Text += "   ";
							   }
                      time(&end);
					  search_time = long int (end-start);
			          textBox6->Text += System::Convert::ToString(search_time);
				 }
			 } 
		}
		else
			MessageBox::Show("Массив не может быть сгенерирован.\nУдалите действующий массив.", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);

}
// Функция сохранения в файл
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			    Stream^ myStream;
                SaveFileDialog ^ saveFileDialog1 = gcnew SaveFileDialog();
				saveFileDialog1->Filter = "Text Files|*.txt";
				saveFileDialog1->Title = "Введите название текстового файла с расширением .txt";

		        if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		        {
	                if ((myStream=saveFileDialog1->OpenFile()) != nullptr)
				    {
					      String^ outfilename = this->textBox7->Text;
                          array<unsigned char>^ arr = System::Text::Encoding::GetEncoding(866)->GetBytes(outfilename);
						  myStream->Write(arr, 0, outfilename->Length);
                          myStream->Close();
						  MessageBox::Show("Массив успешно записан в файл");
						  p = true;
					}
				}
		 }
//Чтение из файла
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		if(de == true)
		{
			 if(c == true)
			 {
				OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
				openFileDialog1->Filter = "Text Files|*.txt";
				openFileDialog1->Title = "Выберите текстовый файл с расширением txt";

		        if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		        {
	                if ((openFileDialog1->OpenFile()) != nullptr)
				    {
					      String ^ filename = openFileDialog1->FileName;
		                  filename1 = (char*)(void*)Marshal::StringToHGlobalAnsi(filename);
						  d = aaa(filename1, &h1);
						  if(filename1)
						  {
							   MessageBox::Show("Массив считан из файла", "Ок", MessageBoxButtons::OK);
						       for (i = 0; i < h1; i++)
							   {
					                textBox1->Text += System::Convert::ToString(d[i]);
									if(i < (h1 - 1))
										textBox1->Text += "   ";
							   }
							   p = true;
							   f = false;
							   c = false;
							   this->textBox4->Text = System::Convert::ToString(h1);
							   this->textBox4->ReadOnly = true;
						  }
				    }
		        }
			 }
			 else
				 MessageBox::Show("Нельзя считать массив! Удалите действующий массив и повторите попытку.", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else
			 MessageBox::Show("Нельзя считать массив! Удалите действующий массив и повторите попытку.", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label8_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void textBox8_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

		 }
// Сортировка  массива библиотечной функцией
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	    time_t start,end;
		time(&start);
		qsort(d, h1, sizeof(int), cmp );
			for (i = 0; i < h1; i++)
				{
					textBox7->Text += System::Convert::ToString(d[i]);
					if(i < (h1 - 1))
						textBox7->Text += "   ";
				}
		time(&end);
		search_time = long int (end-start);
		textBox8->Text += System::Convert::ToString(search_time);
}

void sort_s_vizual(int *d, int from1, int to1) 
{
    int j, k;
    int x, temp;
    if (from1 >= to1){
       return;
    }
    k = from1;
    j = to1;
    x = d[(from1+to1)/2];
    temp = d[k];
	while (k <= j) 
	{
		while (d[k] < x) 
		{
		k++;
		}
		while (d[j] > x) {
		j--;
		};
		if (k <= j) 
		{
		temp = d[k]; 
		d[k] = d[j];
		d[j] = temp;
		Matr = (int**)realloc(Matr, (kolvo1+1)*sizeof(int*));
		Matr[kolvo1] = (int*)malloc(h1*sizeof(int));
		for(int l = 0; l < h1; l ++)
			Matr[kolvo1][l] = d[l];

		kolvo1 ++;
		k++;
		j--;
		}
	}
	sort_s_vizual(d, from1, j);
	sort_s_vizual(d, k, to1);
}
};
}
