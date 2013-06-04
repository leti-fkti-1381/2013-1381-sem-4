#include "lib.h"
#pragma once


namespace lr_4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 575);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(150, 25);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Построить граф";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(472, 575);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(150, 25);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Построить остов";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(168, 581);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(196, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Сначала необходимо построить граф";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 533);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(256, 39);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Исходные данные берутся из файла input.txt;\r\nПолученный остов сохраняется в файл " 
				L"output.txt;\r\nМаксимальный размер графа 20 вершиин";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(634, 612);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Form1";
			this->Text = L"Нахождение минимального остового дерева";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				getData ();

				if (Vertex > max_vertex || Vertex <= 0)
					label1->Text = "Неверное количество вершин!!!";
				else
				{
					makeTree = true;
					Graphics^ g = this->CreateGraphics();
					// Вершины графа
					for (int i = 0; i < Vertex; i++)
						g->DrawLine(gcnew Pen(Color::Green, 8), int(point_x[i])-4, int(point_y[i])-4, int(point_x[i])+4, int(point_y[i])+4);
					// Ребра графа и стоимости
					for (int i = 0; i < Vertex; i++)
						for (int j = i+1; j < Vertex; j++)
							if (arr_graph[i][j] != 0)
							{
								g->DrawLine(gcnew Pen(Color::Green, 3), int(point_x[i]), int(point_y[i]), int(point_x[j]), int(point_y[j])); //Линия
								g->DrawString(System::Convert::ToString(arr_graph[i][j]), gcnew Drawing::Font("Arial", 24), Brushes::GreenYellow, (int(point_x[i])+int(point_x[j]))/2, (int(point_y[i])+int(point_y[j]))/2);
							}
					label1->Text = "Граф построен";
				}
			}


	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				if (makeTree == false)
					label1->Text = "СНАЧАЛА ПОСТРОЙТЕ ГРАФ!!!";
				else
				{
					Search (); // Поиск остова

					Graphics^ g = this->CreateGraphics();
					// Ребра остова
					for (int i = 0; i < Vertex; i++)
						for (int j = i+1; j < Vertex; j++)
							if (temp_arr[i][j] != 0)
							{
								g->DrawLine(gcnew Pen(Color::Cyan, 3), int(point_x[i]), int(point_y[i]), int(point_x[j]), int(point_y[j])); //Линия
							}
					label1->Text = "Остов построен";
				}
			}
};
}

