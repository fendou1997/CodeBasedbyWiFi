using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using CCWin;
using CCWin.Win32;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.IO;
using System.Threading;
using System.Data.SqlClient;
using System.Configuration;
using System.Windows.Forms.DataVisualization.Charting;
using Model;
namespace PowerMonitor
{
    public delegate void MyDelegate(object o);

    public partial class Form2 : Skin_DevExpress
    {
        //------------------------------------数据库操作------------------------------------------//
        private Queue<double> dataQueue1 = new Queue<double>(100);
        private Queue<double> dataQueue2 = new Queue<double>(100);
        private Queue<double> dataQueue3 = new Queue<double>(100);
        private Queue<double> dataQueue4 = new Queue<double>(100);
     
        private bool leafflag = false;
        private int num = 5;//每次删除增加几个点
        //添加数据库查询操作
        private SqlConnection conn = new SqlConnection(ConfigurationSettings.AppSettings["ConnString"]);
        private SqlCommand cmd = new SqlCommand();
        //------------------------------------------网络操作-----------------------------------------------------//

     




        private bool isTextBoxNotEmpty = true; //判断输入文本框是否为空
        private UdpClient udpSend;
        private UdpClient udpReceive;
        private Thread thread1;



        //---------------------------------------------------------------------------------------------------//
        public Form2()
        {
            
            InitializeComponent();
            LoadData();
            this.chat.Visible = false;
            this.skinPanel1.Visible = false;
           


        }

        #region 
        private void skinLabel10_Click(object sender, EventArgs e)
        {
        }
        //---------------------------------------------------------------------------------------------//
        //--------------------------------------------可视化显示---------------------------------------//
        /// <summary>
        /// 初始化图表1,2,3,4
        /// </summary>
        private void InitChart1()
        {
            //定义图表区域
            this.chart1.ChartAreas.Clear();
            ChartArea chartArea1 = new ChartArea("C1");
            this.chart1.ChartAreas.Add(chartArea1);
            //定义存储和显示点的容器
            this.chart1.Series.Clear();
            Series series1 = new Series("S1");
            series1.ChartArea = "C1";
            this.chart1.Series.Add(series1);
            //设置图表显示样式
            this.chart1.ChartAreas[0].AxisY.Minimum = 0;
            this.chart1.ChartAreas[0].AxisY.Maximum = 100;
            this.chart1.ChartAreas[0].AxisX.Interval = 5;
            this.chart1.ChartAreas[0].AxisX.MajorGrid.LineColor = System.Drawing.Color.Silver;
            this.chart1.ChartAreas[0].AxisY.MajorGrid.LineColor = System.Drawing.Color.Silver;
            //设置标题
            this.chart1.Titles.Clear();
            this.chart1.Titles.Add("S01");
            this.chart1.Titles[0].Text = "电压显示";
            this.chart1.Titles[0].ForeColor = Color.RoyalBlue;
            this.chart1.Titles[0].Font = new System.Drawing.Font("Microsoft Sans Serif", 6F);
            //设置图表显示样式
            this.chart1.Series[0].Color = Color.Red;
            if (skinRadioButton3.Checked)
            {
                this.chart1.Titles[0].Text = string.Format("电压 {0} 显示", skinRadioButton3.Text);
                this.chart1.Series[0].ChartType = SeriesChartType.Line;
            }
            if (skinRadioButton2.Checked)
            {
                this.chart1.Titles[0].Text = string.Format("电压 {0} 显示", skinRadioButton2.Text);
                this.chart1.Series[0].ChartType = SeriesChartType.Spline;
            }
            this.chart1.Series[0].Points.Clear();
        }
        private void InitChart2()
        {
            //定义图表区域
            this.chart2.ChartAreas.Clear();
            ChartArea chartArea1 = new ChartArea("C1");
            this.chart2.ChartAreas.Add(chartArea1);
            //定义存储和显示点的容器
            this.chart2.Series.Clear();
            Series series1 = new Series("S1");
            series1.ChartArea = "C1";
            this.chart2.Series.Add(series1);
            //设置图表显示样式
            this.chart2.ChartAreas[0].AxisY.Minimum = 0;
            this.chart2.ChartAreas[0].AxisY.Maximum = 100;
            this.chart2.ChartAreas[0].AxisX.Interval = 5;
            this.chart2.ChartAreas[0].AxisX.MajorGrid.LineColor = System.Drawing.Color.Silver;
            this.chart2.ChartAreas[0].AxisY.MajorGrid.LineColor = System.Drawing.Color.Silver;
            //设置标题
            this.chart2.Titles.Clear();
            this.chart2.Titles.Add("S01");
            this.chart2.Titles[0].Text = "电流显示";
            this.chart2.Titles[0].ForeColor = Color.RoyalBlue;
            this.chart2.Titles[0].Font = new System.Drawing.Font("Microsoft Sans Serif", 6F);
            //设置图表显示样式
            this.chart2.Series[0].Color = Color.Red;
            if (skinRadioButton4.Checked)
            {
                this.chart2.Titles[0].Text = string.Format("电流 {0} 显示", skinRadioButton3.Text);
                this.chart2.Series[0].ChartType = SeriesChartType.Line;
            }
            if (skinRadioButton5.Checked)
            {
                this.chart2.Titles[0].Text = string.Format("电流 {0} 显示", skinRadioButton2.Text);
                this.chart2.Series[0].ChartType = SeriesChartType.Spline;
            }
            this.chart2.Series[0].Points.Clear();
        }
        private void InitChart3()
        {
            //定义图表区域
            this.chart3.ChartAreas.Clear();
            ChartArea chartArea1 = new ChartArea("C1");
            this.chart3.ChartAreas.Add(chartArea1);
            //定义存储和显示点的容器
            this.chart3.Series.Clear();
            Series series1 = new Series("S1");
            series1.ChartArea = "C1";
            this.chart3.Series.Add(series1);
            //设置图表显示样式
            this.chart3.ChartAreas[0].AxisY.Minimum = 0;
            this.chart3.ChartAreas[0].AxisY.Maximum = 100;
            this.chart3.ChartAreas[0].AxisX.Interval = 5;
            this.chart3.ChartAreas[0].AxisX.MajorGrid.LineColor = System.Drawing.Color.Silver;
            this.chart3.ChartAreas[0].AxisY.MajorGrid.LineColor = System.Drawing.Color.Silver;
            //设置标题
            this.chart3.Titles.Clear();
            this.chart3.Titles.Add("S01");
            this.chart3.Titles[0].Text = "风速显示";
            this.chart3.Titles[0].ForeColor = Color.RoyalBlue;
            this.chart3.Titles[0].Font = new System.Drawing.Font("Microsoft Sans Serif", 6F);
            //设置图表显示样式
            this.chart3.Series[0].Color = Color.Red;

            this.chart3.Series[0].ChartType = SeriesChartType.Line;

            this.chart3.Series[0].Points.Clear();
        }
        private void InitChart4()
        {
            //定义图表区域
            this.chart4.ChartAreas.Clear();
            ChartArea chartArea1 = new ChartArea("C1");
            this.chart4.ChartAreas.Add(chartArea1);
            //定义存储和显示点的容器
            this.chart4.Series.Clear();
            Series series1 = new Series("S1");
            series1.ChartArea = "C1";
            this.chart4.Series.Add(series1);
            //设置图表显示样式
            this.chart4.ChartAreas[0].AxisY.Minimum = 0;
            this.chart4.ChartAreas[0].AxisY.Maximum = 100;
            this.chart4.ChartAreas[0].AxisX.Interval = 5;
            this.chart4.ChartAreas[0].AxisX.MajorGrid.LineColor = System.Drawing.Color.Silver;
            this.chart4.ChartAreas[0].AxisY.MajorGrid.LineColor = System.Drawing.Color.Silver;
            //设置标题
            this.chart4.Titles.Clear();
            this.chart4.Titles.Add("S01");
            this.chart4.Titles[0].Text = "温度显示";
            this.chart4.Titles[0].ForeColor = Color.RoyalBlue;
            this.chart4.Titles[0].Font = new System.Drawing.Font("Microsoft Sans Serif", 6F);
            //设置图表显示样式
            this.chart4.Series[0].Color = Color.Red;

            this.chart4.Series[0].ChartType = SeriesChartType.Line;

            this.chart4.Series[0].Points.Clear();
        }

        private void LoadData()
        {
            cmd.Parameters.Clear();
            cmd.Connection = conn;
            SqlDataAdapter adp = new SqlDataAdapter(cmd);
            DataSet ds = new DataSet();

            cmd.CommandText = "GetAllPlace";
            cmd.CommandType = CommandType.StoredProcedure;
            adp.Fill(ds, "place");
            skinComboBox1.DataSource = ds.Tables["place"];
            skinComboBox1.DisplayMember = "No";

            skinComboBox1.ValueMember = "Place";
            skinComboBox2.DataSource = ds.Tables["place"];
            skinComboBox2.DisplayMember = "place";
            skinComboBox2.ValueMember = "No";
            skinComboBox3.DataSource = ds.Tables["place"];
            skinComboBox3.DisplayMember = "No";
            skinComboBox3.ValueMember = "place";
            skinComboBox4.DataSource = ds.Tables["place"];
            skinComboBox4.DisplayMember = "place";
            skinComboBox4.ValueMember = "No";
            this.chat.Visible = false;
            this.skinPanel1.Visible = false;
      

        }

        private void UpdateQueueValue1()
        {

            if (dataQueue1.Count > 100)
            {
                //先出列
                for (int i = 0; i < num; i++)
                {
                    dataQueue1.Dequeue();
                }
            }
            if (skinRadioButton3.Checked)
            {
                Random r = new Random();
                for (int i = 0; i < num; i++)
                {
                    dataQueue1.Enqueue(r.Next(0, 100));
                }
            }
            if (skinRadioButton2.Checked)
            {
                    int curValue = 0;
                for (int i = 0; i < num; i++)
                {
                    //对curValue只取[0,360]之间的值
                    curValue = curValue % 360;
                    //对得到的正玄值，放大50倍，并上移50
                    dataQueue1.Enqueue((50 * Math.Sin(curValue * Math.PI / 180)) + 50);
                    curValue = curValue + 10;
                }
            }
        }

        /// <summary>
        /// 电压初始化
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void skinButton2_Click(object sender, EventArgs e)
        {
            InitChart1();
        }
        /// <summary>
        /// 电流初始化
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void skinButton7_Click(object sender, EventArgs e)
        {
            InitChart2();
        }
        /// <summary>
        /// 风速初始化
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void skinButton10_Click(object sender, EventArgs e)
        {
            InitChart3();
        }
        /// <summary>
        /// 温度初始化
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void skinButton13_Click(object sender, EventArgs e)
        {
            InitChart4();
        }

        /// <summary>
        /// 定时器1
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer1_Tick(object sender, EventArgs e)
        {
            UpdateQueueValue1();
            this.chart1.Series[0].Points.Clear();
            for (int i = 0; i < dataQueue1.Count; i++)
            {
                this.chart1.Series[0].Points.AddXY((i + 1), dataQueue1.ElementAt(i));
            }
        }
        /// <summary>
        ///  电压检测开始
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void skinButton3_Click(object sender, EventArgs e)
        {
            this.timer1.Start();
        }
        /// <summary>
        /// 电压检测停止
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void skinButton4_Click(object sender, EventArgs e)
        {
            this.timer1.Stop();
        }


        private void UpdateQueueValue2()
        {

            if (dataQueue2.Count > 100)
            {
                //先出列
                for (int i = 0; i < num; i++)
                {
                    dataQueue2.Dequeue();
                }
            }
            if (skinRadioButton4.Checked)
            {
                Random r = new Random();
                for (int i = 0; i < num; i++)
                {
                    dataQueue2.Enqueue(r.Next(0, 100));
                }
            }
            if (skinRadioButton5.Checked)
            {
                int curValue = 0;
                for (int i = 0; i < num; i++)
                {
                    //对curValue只取[0,360]之间的值
                    curValue = curValue % 360;
                    //对得到的正玄值，放大50倍，并上移50
                    dataQueue2.Enqueue((50 * Math.Sin(curValue * Math.PI / 180)) + 50);
                    curValue = curValue + 10;
                }
            }
        }
        /// <summary>
        /// 定时器2
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer2_Tick(object sender, EventArgs e)
        {
            UpdateQueueValue2();
            this.chart2.Series[0].Points.Clear();
            for (int i = 0; i < dataQueue2.Count; i++)
            {
                this.chart2.Series[0].Points.AddXY((i + 1), dataQueue2.ElementAt(i));
            }
        }
        /// <summary>
        /// 电流检测开始
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void skinButton6_Click(object sender, EventArgs e)
        {
            this.timer2.Start();
        }
        /// <summary>
        /// 电流检测停止
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void skinButton5_Click(object sender, EventArgs e)
        {
            this.timer2.Stop();
        }

        private void UpdateQueueValue3()
        {

            if (dataQueue3.Count > 100)
            {
                //先出列
                for (int i = 0; i < num; i++)
                {
                    dataQueue3.Dequeue();
                }
            }

            Random r = new Random();
            for (int i = 0; i < num; i++)
            {
                dataQueue3.Enqueue(r.Next(0, 100));
            }


        }
        /// <summary>
        /// 定时器3
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer3_Tick(object sender, EventArgs e)
        {
            UpdateQueueValue3();
            this.chart3.Series[0].Points.Clear();
            for (int i = 0; i < dataQueue3.Count; i++)
            {
                this.chart3.Series[0].Points.AddXY((i + 1), dataQueue3.ElementAt(i));
            }
        }

        private void skinButton9_Click(object sender, EventArgs e)
        {
            this.timer3.Start();
        }

        private void skinButton8_Click(object sender, EventArgs e)
        {
            this.timer3.Stop();
        }


        private void UpdateQueueValue4()
        {

            if (dataQueue4.Count > 100)
            {
                //先出列
                for (int i = 0; i < num; i++)
                {
                    dataQueue4.Dequeue();
                }
            }

            Random r = new Random();
            for (int i = 0; i < num; i++)
            {
                dataQueue4.Enqueue(r.Next(0, 100));
            }


        }
        private void timer4_Tick(object sender, EventArgs e)
        {
            UpdateQueueValue4();
            this.chart4.Series[0].Points.Clear();
            for (int i = 0; i < dataQueue4.Count; i++)
            {
                this.chart4.Series[0].Points.AddXY((i + 1), dataQueue4.ElementAt(i));
            }
        }

        private void skinButton12_Click(object sender, EventArgs e)
        {
            this.timer4.Start();
        }

        private void skinButton11_Click(object sender, EventArgs e)
        {
            this.timer4.Stop();
        }
        /// <summary>
        /// 控制开闭
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer5_Tick(object sender, EventArgs e)
        {

        }

        private void skinRadioButton6_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void skinRadioButton6_Click(object sender, EventArgs e)
        {
            if (skinRadioButton6.Checked)
            {
                this.timer1.Stop();
                this.timer2.Stop();
                this.timer3.Stop();
                this.timer4.Stop();
                this.timer5.Stop();
            }
        }

        private void skinButton14_Click(object sender, EventArgs e)
        {
            skinChatRichTextBox2.Text = "";

        }
        /// <summary>
        /// 保存数据
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void skinCheckBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (skinCheckBox3.Checked)
            {
                try
                {





                }
                catch
                {


                }
                MessageBox.Show("保存成功！", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);

            }
        }
        /// <summary>
        /// 隐藏下面一层
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WiFi_Click(object sender, EventArgs e)
        {
            this.chat.Visible = true;
            this.skinPanel1.Visible = false;
          


        }

        private void Monitor_Click(object sender, EventArgs e)
        {
            this.chat.Visible = false;
            this.skinPanel1.Visible = true;
           
        }

        private void Close_Click(object sender, EventArgs e)
        {
            this.Close();
            thread1.Abort();
        }
        #endregion
        //----------------------------------------------通信--------------------------------------------------------//
      
        public void sentMessage()
        {
            if (this.skinChatRichTextBox2.Text == "")
            {
                this.skinChatRichTextBox2.Text = "输入消息不能为空...";
                this.skinChatRichTextBox2.BackColor = Color.OldLace;
                this.isTextBoxNotEmpty = false;

            }
            else
            {

                this.isTextBoxNotEmpty = true;

            }
            if (isTextBoxNotEmpty)
            {
                byte[] Buff1 = new byte[1024000];//定义一个buff来存储消息
                try
                {
                    //发送到对方的信息框中
                    udpSend = new UdpClient();
                    udpSend.EnableBroadcast = true;
                    IPEndPoint iep = new IPEndPoint(IPAddress.Parse("192.168.4.1"), 8080);
                    Buff1 = System.Text.Encoding.Default.GetBytes(skinChatRichTextBox2.Text);
                    udpSend.Send(Buff1, Buff1.Length, iep);
                    //向自己的显示框中显示发送信息
                    this.skinChatRichTextBox1.AppendRichText(DateTime.Now.ToLongTimeString() + "\r\n",
                     new Font(this.Font, FontStyle.Regular), skinChatRichTextBox2.ForeColor = System.Drawing.Color.Green);

                    this.skinChatRichTextBox1.AppendRtf(this.skinChatRichTextBox2.Rtf);
                    //this.txtRMsg.AppendTextAsRtf("\n");
                    this.skinChatRichTextBox1.Select(skinChatRichTextBox1.Text.Length, 0);
                    this.skinChatRichTextBox1.ScrollToCaret();
                    //清空输入框
                    this.skinChatRichTextBox2.Text = string.Empty;
                    this.skinChatRichTextBox2.Focus();
                }
                catch
                {

                    this.skinChatRichTextBox1.AppendText(DateTime.Now.ToLongTimeString() + " 发送消息失败！" + "\r\n");

                }
            }
        }



        //显示接收消息

      
        private void btnDl_Click(object sender, EventArgs e)
        {
            sentMessage();
        }

        public void ReceiveMessage()
        {

            //byte[] Buff = new byte[1024000];//定义一个buff来存储消息
            //IPEndPoint remoteIpEndPoint = new IPEndPoint(IPAddress.Any,8080);
            //udpReceive = new UdpClient(remoteIpEndPoint);
            //IPEndPoint iep = new IPEndPoint(IPAddress.Any, 0);
            int recv;
            byte[] Buff = new byte[1024];

            //得到本机IP，设置TCP端口号         
            IPEndPoint ip = new IPEndPoint(IPAddress.Any, 8080);
            Socket newsock = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

            //绑定网络地址
            newsock.Bind(ip);

            IPEndPoint sender = new IPEndPoint(IPAddress.Any, 0);
            EndPoint Remote = (EndPoint)(sender);

            while (true)
            {
                if (leafflag)
                {
                    try
                    {
                        recv = newsock.ReceiveFrom(Buff, ref Remote);
                        this.skinChatRichTextBox1.AppendRichText("From : 192.168.4.2" + " " + DateTime.Now.ToLongTimeString() + "\r\n",
                        new Font(this.Font, FontStyle.Regular), skinChatRichTextBox1.ForeColor = System.Drawing.Color.Blue);
                        this.skinChatRichTextBox1.SelectionColor = Color.Red;
                        this.skinChatRichTextBox1.AppendText(Encoding.Default.GetString(Buff, 0, Buff.Length) + "\n");
                        //this.txtRMsg.AppendTextAsRtf("\n");
                        this.skinChatRichTextBox1.ForeColor = Color.Black;
                        this.skinChatRichTextBox1.Select(skinChatRichTextBox1.Text.Length, 0);
                        this.skinChatRichTextBox1.ScrollToCaret();


                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.ToString());

                    }
                    finally
                    {



                    }
                }
            }
        }

      
        public void skinRadioButton1_CheckedChanged(object sender, EventArgs e)
        {

            if (skinRadioButton1.Checked == true)
            {
                leafflag = true;
            }
            else
            {
                leafflag = false;
                udpSend.Close();
            }
        }

        private void duankai_CheckedChanged(object sender, EventArgs e)
        {

        }

      
        /// <summary>
        /// 当7被选中则开始线程接收数据
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void skinRadioButton7_CheckedChanged(object sender, EventArgs e)
        {
            if (skinRadioButton7.Checked == true)
            {
                leafflag = true;
            }
            if (skinRadioButton6.Checked == true)
            {
                leafflag = false;

            }
        }

        private void Form2_Load_1(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            thread1 = new Thread(new ThreadStart(ReceiveMessage));
            thread1.Start();

        }

        private void Form2_FormClosed(object sender, FormClosedEventArgs e)
        {
            thread1.Abort();
        }





        //----------------------------------------------------------------------------------------------------------//
    }
    public class MyClass
    {
        //利用上面的代理声明一个事件
        public event MyDelegate MyEvent;
        //定义一个方法调用事件
        public MyClass()
        { }
        public void FireAway(object o)
        {
            if (MyEvent != null)
            {
                MyEvent(o);

            }

        }

    }

}
