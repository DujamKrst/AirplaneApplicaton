#pragma once

namespace Zavrsnirad {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Diagnostics;
	using namespace System::Drawing;


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  text_box_rezultat;
	private: array<double> ^niz;
	private: array<double> ^resultarray;
	private: array<double> ^kutarray;


	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;

	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Button^  button4;


	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::Windows::Forms::CheckBox^  checkBox4;
	private: System::Windows::Forms::CheckBox^  checkBox5;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label8;

	protected:

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->text_box_rezultat = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox4 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(446, 40);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Izračunaj";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(3, 42);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Vodiljivost snijega";
			// 
			// textBox2
			// 
			this->textBox2->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->textBox2->Location = System::Drawing::Point(126, 38);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 3;
			this->textBox2->Text = L"0,1";
			this->textBox2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::textBox2_MouseClick);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(3, 84);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(107, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Dielektricnost snijega";
			// 
			// textBox3
			// 
			this->textBox3->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->textBox3->Location = System::Drawing::Point(126, 81);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 5;
			this->textBox3->Text = L"1";
			this->textBox3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::textBox3_MouseClick);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 126);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(84, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Vodljivost zemlje";
			// 
			// textBox4
			// 
			this->textBox4->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->textBox4->Location = System::Drawing::Point(126, 123);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(100, 20);
			this->textBox4->TabIndex = 7;
			this->textBox4->Text = L"0,02";
			this->textBox4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::textBox4_MouseClick);
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox4_TextChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 176);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(103, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Dielektricnost zemlje";
			// 
			// textBox5
			// 
			this->textBox5->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->textBox5->Location = System::Drawing::Point(126, 173);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 20);
			this->textBox5->TabIndex = 9;
			this->textBox5->Text = L"9";
			this->textBox5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::textBox5_MouseClick);
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox5_TextChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(3, 217);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(81, 13);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Deblijna snijega";
			// 
			// textBox6
			// 
			this->textBox6->ForeColor = System::Drawing::SystemColors::ControlDarkDark;
			this->textBox6->Location = System::Drawing::Point(126, 214);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 20);
			this->textBox6->TabIndex = 11;
			this->textBox6->Text = L"0,02";
			this->textBox6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::textBox6_MouseClick);
			// 
			// text_box_rezultat
			// 
			this->text_box_rezultat->Location = System::Drawing::Point(697, 45);
			this->text_box_rezultat->Name = L"text_box_rezultat";
			this->text_box_rezultat->Size = System::Drawing::Size(100, 20);
			this->text_box_rezultat->TabIndex = 13;
			this->text_box_rezultat->Text = L" ";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(622, 45);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(71, 13);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Kut Slijetanja:";
			this->label7->Click += gcnew System::EventHandler(this, &MyForm::label7_Click);
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(364, 111);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->Legend = L"Legend1";
			series1->Name = L"Kut Sljetanja";
			series1->YValueType = System::Windows::Forms::DataVisualization::Charting::ChartValueType::Double;
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(509, 459);
			this->chart1->TabIndex = 15;
			this->chart1->Text = L"chart1";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(157, 456);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(162, 50);
			this->button3->TabIndex = 17;
			this->button3->Text = L"Nova analiza";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(704, 554);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(89, 34);
			this->button4->TabIndex = 18;
			this->button4->Text = L"Exit";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(14, 265);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(64, 13);
			this->label9->TabIndex = 21;
			this->label9->Text = L"Broj koraka:";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(237, 38);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(35, 17);
			this->checkBox1->TabIndex = 22;
			this->checkBox1->Text = L"1.";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(237, 80);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(35, 17);
			this->checkBox2->TabIndex = 23;
			this->checkBox2->Text = L"2.";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(237, 123);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(35, 17);
			this->checkBox3->TabIndex = 24;
			this->checkBox3->Text = L"3.";
			this->checkBox3->UseVisualStyleBackColor = true;
			// 
			// checkBox4
			// 
			this->checkBox4->AutoSize = true;
			this->checkBox4->Checked = true;
			this->checkBox4->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox4->Location = System::Drawing::Point(237, 173);
			this->checkBox4->Name = L"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(35, 17);
			this->checkBox4->TabIndex = 25;
			this->checkBox4->Text = L"4.";
			this->checkBox4->UseVisualStyleBackColor = true;
			// 
			// checkBox5
			// 
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(237, 214);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(35, 17);
			this->checkBox5->TabIndex = 26;
			this->checkBox5->Text = L"5.";
			this->checkBox5->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(101, 262);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 27;
			this->textBox1->Text = L"5";
			// 
			// textBox7
			// 
			this->textBox7->Location = System::Drawing::Point(10, 337);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(54, 20);
			this->textBox7->TabIndex = 28;
			this->textBox7->Text = L"9";
			// 
			// textBox8
			// 
			this->textBox8->Location = System::Drawing::Point(89, 337);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(49, 20);
			this->textBox8->TabIndex = 29;
			this->textBox8->Text = L"15";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(14, 321);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(47, 13);
			this->label1->TabIndex = 30;
			this->label1->Text = L"Početak";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(98, 321);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(25, 13);
			this->label8->TabIndex = 31;
			this->label8->Text = L"Kraj";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(858, 622);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->checkBox5);
			this->Controls->Add(this->checkBox4);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->text_box_rezultat);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"Zavrsni rad";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::MyForm_KeyPress);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		int n = 0;
		String ^ para2 = this->textBox2->Text;
		String ^ para3 = this->textBox3->Text;
		String ^ para4 = this->textBox4->Text;
		String ^ para5 = this->textBox5->Text;
		String ^ para6 = this->textBox6->Text;
		String ^ ns = this->textBox1->Text;
		String ^ starts = this->textBox7->Text;
		String ^ ends = this->textBox8->Text;

		niz = gcnew array<double>(9);


		double start = 0;
		double end = 0;
		double alpha = 0;

		try {
			
			n = Convert::ToInt32(ns);
			niz[0] = Convert::ToDouble(para2);
			niz[1] = Convert::ToDouble(para3);
			niz[2] = Convert::ToDouble(para4);
			niz[3] = Convert::ToDouble(para5);
			niz[4] = Convert::ToDouble(para6);
			start = Convert::ToDouble(starts);
			end = Convert::ToDouble(ends);
			
		}
		catch (...)
		{
			System:MessageBox::Show("Unesite točne parametre!");
		}


		alpha = (end - start) / (n - 1);
		String ^ strCmdText;
		resultarray = gcnew array<double>(n);
		kutarray = gcnew array<double>(n);

		for (int i = 0; i < n; i++)
		{
			try {
			


					if (checkBox1->Checked == true)
					{
						niz[0] = start;
						resultarray[i] = niz[0];
						start += alpha;
						strCmdText = niz[0] + " " + niz[1] + " " + niz[2] + " " + niz[3] + " " + niz[4];



						Process ^ p = System::Diagnostics::Process::Start("Kut.exe", strCmdText);
						p->WaitForExit();
						int temp = p->ExitCode;
						double result = Convert::ToDouble(temp);
						result = result / 100;
						kutarray[i] = result;



						String ^ rezultat = " ";
						rezultat = Convert::ToString(result);
						this->text_box_rezultat->Text = rezultat;



					}
					else if (checkBox2->Checked == true)
					{
						niz[1] = start;
						resultarray[i] = niz[1];
						start += alpha;
						strCmdText = niz[0] + " " + niz[1] + " " + niz[2] + " " + niz[3] + " " + niz[4];

						Process ^ p = System::Diagnostics::Process::Start("Kut.exe", strCmdText);
						p->WaitForExit();
						int temp = p->ExitCode;
						double result = Convert::ToDouble(temp);
						result = result / 100;
						kutarray[i] = result;

						String ^ rezultat = " ";
						rezultat = Convert::ToString(result);
						this->text_box_rezultat->Text = rezultat;



					}
					else if (checkBox3->Checked == true)
					{
						niz[2] = start;
						resultarray[i] = niz[2];
						start += alpha;
						strCmdText = niz[0] + " " + niz[1] + " " + niz[2] + " " + niz[3] + " " + niz[4];

						Process ^ p = System::Diagnostics::Process::Start("Kut.exe", strCmdText);
						p->WaitForExit();
						int temp = p->ExitCode;
						double result = Convert::ToDouble(temp);
						result = result / 100;
						kutarray[i] = result;

						String ^ rezultat = " ";
						rezultat = Convert::ToString(result);
						this->text_box_rezultat->Text = rezultat;



					}
					else if (checkBox4->Checked == true)
					{
						niz[3] = start;
						resultarray[i] = niz[3];
						start += alpha;
						strCmdText = niz[0] + " " + niz[1] + " " + niz[2] + " " + niz[3] + " " + niz[4];

						Process ^ p = System::Diagnostics::Process::Start("Kut.exe", strCmdText);
						p->WaitForExit();
						int temp = p->ExitCode;
						double result = Convert::ToDouble(temp);
						result = result / 100;
						kutarray[i] = result;

						String ^ rezultat = " ";
						rezultat = Convert::ToString(result);
						this->text_box_rezultat->Text = rezultat;


					}
					else if (checkBox5->Checked == true)
					{
						niz[4] = start;
						resultarray[i] = niz[4];
						start += alpha;
						strCmdText = niz[0] + " " + niz[1] + " " + niz[2] + " " + niz[3] + " " + niz[4];

						Process ^ p = System::Diagnostics::Process::Start("Kut.exe", strCmdText);
						p->WaitForExit();
						int temp = p->ExitCode;
						double result = Convert::ToDouble(temp);
						result = result / 100;
						kutarray[i] = result;

						String ^ rezultat = " ";
						rezultat = Convert::ToString(result);
						this->text_box_rezultat->Text = rezultat;
					}



			}
			catch (...)
			{
				this->text_box_rezultat->Text = "wat";

			System:MessageBox::Show("Odaberite parametar za analizu ( CheckBox )!");
			}


			int n;
			String ^ ns = this->textBox1->Text;
			n = Convert::ToInt32(ns);
			ArrayList ^ xvals = gcnew ArrayList();

			ArrayList ^ yvals = gcnew ArrayList();

			for (unsigned int i = 0; i<n; i++)
			{
				yvals->Add(kutarray[i]);
				xvals->Add(resultarray[i]);
			}

			this->chart1->Series[0]->Points->DataBindXY(xvals, yvals);


		}




	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void label7_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void MyForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	}
			 //Hover click

	private: System::Void textBox2_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		this->textBox2->Text = L"";
		this->textBox2->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void textBox3_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		this->textBox3->Text = L"";
		this->textBox3->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void textBox4_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		this->textBox4->Text = L"";
		this->textBox4->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void textBox5_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		this->textBox5->Text = L"";
		this->textBox5->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void textBox6_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		this->textBox6->Text = L"";
		this->textBox6->ForeColor = System::Drawing::Color::Black;
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	

		
		



	}

			 //Povecavanje za odredeni broj n
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Controls->Clear();
		InitializeComponent();

	
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		Application::Exit();
	}
	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {

		String ^ Spovecaj_korak;
		String ^ ispis;
		int povecaj_korak = 0;


	}

	};


}
