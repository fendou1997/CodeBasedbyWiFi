using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Model
{
    public  class PowerData
    {
        /// <summary>
        /// 风速
        /// </summary>
        protected float windspeed;
        public float WindSpeed
        {
            get { return windspeed; }
            set { windspeed = value; }
        }
        /// <summary>
        /// A相电压
        /// </summary>
        protected float voltageA;
        public float VoltageA
        {
            get { return voltageA; }
            set { voltageA = value; }
        }
        /// <summary>
        /// B相电压
        /// </summary>
        protected float voltageB;
        public float VoltageB
        {
            get { return voltageB; }
            set { voltageB = value; }
        }
        /// <summary>
        /// C相电压
        /// </summary>
        protected float voltageC;
        public float VoltageC
        {
            get { return voltageC; }
            set { voltageC = value; }
        }
        /// <summary>
        /// A相电流
        /// </summary>
        protected float currentA;
        public float CurrentA
        {
            get { return currentA; }
            set { currentA = value; }
        }
        /// <summary>
        /// B相电流
        /// </summary>
        protected float currentB;
        public float CurrentB
        {
            get { return currentB; }
            set { currentB = value; }
        }
        /// <summary>
        /// C相电流
        /// </summary>
        protected float currentC;
        public float CurrentC
        {
            get { return currentC; }
            set { currentC = value; }
        }
        /// <summary>
        /// 温度
        /// </summary>
        protected float temperature;
        public float Temperature
        {
            get { return temperature; }
            set { temperature = value; }
        }
        protected int id;
        public int ID
        {
            get { return id; }
            set { id = value; }
        }
        /// <summary>
        /// 
        /// </summary>
        /// <param name="windspeed"></param>
        /// <param name="voltageA"></param>
        /// <param name="voltageB"></param>
        /// <param name="voltageC"></param>
        /// <param name="temperature"></param>
        /// <param name="currentA"></param>
        /// <param name="currentB"></param>
        /// <param name="currentC"></param>
        public PowerData(int id,float windspeed, float voltageA, float voltageB, float voltageC, float temperature, float currentA, float currentB, float currentC)
        {
            this.id = id;
            this.currentA = currentA;
            this.currentB = currentB;
            this.currentC = currentC;
            this.voltageA = voltageA;
            this.voltageA = voltageA;
            this.voltageB = voltageB;
            this.voltageC = voltageC;
            this.windspeed = windspeed;
            this.temperature = temperature;
        }


    }
    /// <summary>
    /// 进行数据的存储（缓存）
    /// </summary>
    public class SaveData
    {
        private List<PowerData> powerdatas;
        public List<PowerData> PowerDatas
        {
             get { return powerdatas; }
             set { powerdatas = value; }
        }
        /// <summary>
        ///构造函数
        /// </summary>
        public SaveData()
        {
            powerdatas = new List<PowerData>();
        }
        public PowerData AddData(int id,float windspeed, float voltageA, float voltageB, float voltageC, float temperature, float currentA, float currentB, float currentC)
        {
            
            PowerData newData = new PowerData(id,windspeed, voltageA, voltageB, voltageC, temperature, currentA, currentB, currentC);
            powerdatas.Add(newData);

            return newData;
        }
        /// <summary>
        /// 获取数据
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public PowerData GetByID(int id)
        {
            foreach (PowerData powerdata in powerdatas)
            {
                if (powerdata.ID== id)
                {
                    return powerdata;
                }
            }
            return null;
        }

    }
 
}
