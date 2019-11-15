using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace BLHermesUDPAtom12_29
{
    public class dataAnalysisTimeSameThread
    {
        public static int[] old_stampTime = new int[7];
        public static int[] old_old_stampTime = new int[7];
        public static ImuQuat[] imuquat_array = new ImuQuat[7];
        public static bool[] wanzhengxing_array = new bool[7];
        public static int currentIndexMax = new int();
        public static int oldCurrentIndex = new int();
        public static int[] longTimeNoData = new int[7];
        public static float[] float_array_t = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
        Thread t_getData;
        public static object g_DATST_lockThis;
        public static int[] syncFailCountNegtive = new int[7];
        public static int[] syncFailCountPositive = new int[7];
        public static int syncSuccessCount = new int();
        public static int tiaobuCount = new int();
        public Action<float[]> onRecvFloat_array;
        //返回值：1：站姿校准成功，2：站姿校准失败，3：坐姿校准成功，4：坐姿校准失败
        public static Action<int> onRecvStandCaliSuccess;
        public float m_currentTime;
        public float m_oldTime;
        public static int longTimeNoSyncCount;
        public static int[] longTimeSyncJumpCount = new int[7];
        public static int[] longTimeSyncJumpRecoverCount = new int[7];
        public static int g_standCaliFailCount = 0;
        public static int g_zuozijiaozhunFlag = 2;

        //获取float_array，静态方法
        public static void getFloatArray(out float[] float_array_return)
        {
            float_array_return = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
            if(g_DATST_lockThis != null)
            {
                lock (g_DATST_lockThis)
                {
                    for (int i = 0; i < 4 * 7 + 3 * 7 + 3 * 7 + 1; i++)
                    {
                        float_array_return[i] = float_array_t[i];
                    }
                }
            }
        }

        //获取错误代码
        public static void getErrorArray(out int[] error_array_return)  //4Hz调用
        {
            error_array_return = new int[100];
            for (int i = 0; i < 100; i++)
            {
                error_array_return[i] = imudatareceiver_plus.error_array[i];
            }

            

            int totalSum = 0;
            int isStandCaliStateEqualTwo = 0;
            for (int iii = 0; iii < 7; iii++)
            {
                if(imudatareceiver_plus.standCalibState[iii] == 1)
                {
                    totalSum += imudatareceiver_plus.standCalibState[iii];
                }
                if (imudatareceiver_plus.standCalibState[iii] == 2)
                {
                    //Console.Write("\n站姿校准延迟延迟!");
                    isStandCaliStateEqualTwo = 1;
                }
            }

            

            if (totalSum >= 7)
            {
                Console.Write("站姿校准完成   全部成功!\n");
                //调用Action
                if (onRecvStandCaliSuccess != null)
                {
                    onRecvStandCaliSuccess(1);
                }
                g_standCaliFailCount = 0;
                imudatareceiver_plus.resetCaliFlag();
            }
            else
            {
                //判断是否刚按下按钮
                if (isStandCaliStateEqualTwo >= 1)
                {
                    g_standCaliFailCount++;
                }
                if (g_standCaliFailCount > 0 && g_standCaliFailCount <= 6)
                {
                    //延迟
                    //string output = "延迟 wanzhengxin 1: " + g_standCaliFailCount + "   " + totalSum + "   " + isStandCaliStateEqualTwo
                    //                + "----   " + imudatareceiver_plus.standCalibState[0]
                    //                + "   " + imudatareceiver_plus.standCalibState[1]
                    //                + "   " + imudatareceiver_plus.standCalibState[2]
                    //                + "   " + imudatareceiver_plus.standCalibState[3]
                    //                + "   " + imudatareceiver_plus.standCalibState[4]
                    //                + "   " + imudatareceiver_plus.standCalibState[5]
                    //                + "   " + imudatareceiver_plus.standCalibState[6];
                    //Console.WriteLine(output);
                    //Console.Write("\n站姿校准延迟!");
                }
                else if (g_standCaliFailCount > 6)
                {
                    //触发
                    imudatareceiver_plus.resetCaliFlag();
                    g_standCaliFailCount = 0;
                    //调用Action
                    if (onRecvStandCaliSuccess != null)
                    {
                        onRecvStandCaliSuccess(2);
                    }
                    Console.Write("\n站姿校准失败!");
                }
            }

            if(g_zuozijiaozhunFlag < 1)
            {
                g_zuozijiaozhunFlag++;
                if(g_zuozijiaozhunFlag == 1)
                {
                    float[] float_array_tmp = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                    dataAnalysisTimeSameThread.getFloatArray(out float_array_tmp);

                    float[] angleCal = new float[12+2];
                    int indexCal = 0;
                    angleCal[indexCal] = HermesCalculator.reqPaziTuibuQuShengAngleToGround(float_array_tmp, 0, 1) - 90; indexCal++;
                    angleCal[indexCal] = HermesCalculator.reqPaziTuibuQuShengAngleToGround(float_array_tmp, 0, 2) - 90; indexCal++;
                    angleCal[indexCal] = HermesCalculator.reqPaziTuibuQuShengAngleToGround(float_array_tmp, 0, 3) - 90; indexCal++;
                    angleCal[indexCal] = HermesCalculator.reqPaziTuibuQuShengAngleToGround(float_array_tmp, 0, 4) - 90; indexCal++;

                    angleCal[indexCal] = HermesCalculator.reqZuoziJiaozhunJiaoxiangqianAngle(float_array_tmp, 0, 1); indexCal++;
                    angleCal[indexCal] = HermesCalculator.reqZuoziJiaozhunJiaoxiangqianAngle(float_array_tmp, 0, 2); indexCal++;
                    angleCal[indexCal] = HermesCalculator.reqZuoziJiaozhunJiaoxiangqianAngle(float_array_tmp, 0, 3); indexCal++;
                    angleCal[indexCal] = HermesCalculator.reqZuoziJiaozhunJiaoxiangqianAngle(float_array_tmp, 0, 4); indexCal++;

                    angleCal[indexCal] = HermesCalculator.reqZuoziJiaozhunTuichangshangAngle(float_array_tmp, 0, 1); indexCal++;
                    angleCal[indexCal] = HermesCalculator.reqZuoziJiaozhunTuichangshangAngle(float_array_tmp, 0, 2); indexCal++;
                    angleCal[indexCal] = HermesCalculator.reqZuoziJiaozhunTuichangshangAngle(float_array_tmp, 0, 3); indexCal++;
                    angleCal[indexCal] = HermesCalculator.reqZuoziJiaozhunTuichangshangAngle(float_array_tmp, 0, 4); indexCal++;

                    angleCal[indexCal] = HermesCalculator.reqMainAngleRelative(float_array_tmp[4 * 5 + 3], float_array_tmp[4 * 5 + 0], float_array_tmp[4 * 5 + 1], float_array_tmp[4 * 5 + 2], 0, 1, 0, 0, 0, 2);
                    indexCal++;
                    angleCal[indexCal] = HermesCalculator.reqMainAngleRelative(float_array_tmp[4 * 6 + 3], float_array_tmp[4 * 6 + 0], float_array_tmp[4 * 6 + 1], float_array_tmp[4 * 6 + 2], 0, 1, 0, 0, 0, 2);
                    indexCal++;

                    for (int i = 0; i < 4; i++)
                    {
                        if (Math.Abs(angleCal[i]) > 60)
                        {
                            //检验坐姿校准
                            if (dataAnalysisTimeSameThread.onRecvStandCaliSuccess != null)
                            {
                                dataAnalysisTimeSameThread.onRecvStandCaliSuccess(4);
                            }
                            Console.Write("\n坐姿校准失败!");
                            return;
                        }
                    }

                    for (int i = 4; i < 8; i++)
                    {
                        if (Math.Abs(angleCal[i]) > 20)
                        {
                            //检验坐姿校准
                            if (dataAnalysisTimeSameThread.onRecvStandCaliSuccess != null)
                            {
                                dataAnalysisTimeSameThread.onRecvStandCaliSuccess(4);
                            }
                            Console.Write("\n坐姿校准失败!");
                            return;
                        }
                    }

                    for (int i = 8; i < 12; i++)
                    {
                        if (Math.Abs(angleCal[i]) > 30)
                        {
                            //检验坐姿校准
                            if (dataAnalysisTimeSameThread.onRecvStandCaliSuccess != null)
                            {
                                dataAnalysisTimeSameThread.onRecvStandCaliSuccess(4);
                            }
                            Console.Write("\n坐姿校准失败!");
                            return;
                        }
                    }

                    for (int i = 12; i < 14; i++)
                    {
                        if (Math.Abs(angleCal[i]) > 45)
                        {
                            //检验坐姿校准
                            if (dataAnalysisTimeSameThread.onRecvStandCaliSuccess != null)
                            {
                                dataAnalysisTimeSameThread.onRecvStandCaliSuccess(4);
                            }
                            Console.Write("\n坐姿校准失败!");
                            return;
                        }
                    }



                    //检验坐姿校准
                    if (dataAnalysisTimeSameThread.onRecvStandCaliSuccess != null)
                    {
                        dataAnalysisTimeSameThread.onRecvStandCaliSuccess(3);
                    }
                    Console.Write("\n坐姿校准成功!");
                }
            }
        }

        public dataAnalysisTimeSameThread()
        {
            g_DATST_lockThis = new object();
        }
        
        //初始化
        public void init()
        {
            if (t_getData != null)
            {
                if (t_getData.IsAlive)
                {
                    //线程关闭
                    t_getData.Abort();
                }
            } 
            //qDebug() << "stopTime";
            currentIndexMax = 0;
            oldCurrentIndex = 0;
            
            for (int i = 0; i < 7; i++)
            {
                wanzhengxing_array[i] = false;
                syncFailCountNegtive[i] = 0;
                syncFailCountPositive[i] = 0;
                longTimeSyncJumpCount[i] = 0;
                longTimeSyncJumpRecoverCount[i] = 0;
            }
            longTimeNoSyncCount = 0;
            t_getData = new Thread(ReciveData);//开启接收消息线程
            t_getData.Start();
        }

        //关闭
        public void close()
        {
            //线程关闭
            t_getData.Abort();
        }

        void ReciveData()
        {
            while (true)
            {
                //确保队列都有值
                int valueNumCount = 0;
                int startIndex = 0;
                int endIndex = 7;
                int totalNumber = 7;
                for (int i = startIndex; i < endIndex; i++)
                {
                    //imuDataReceiver_plus* imu_t = m_imuReceiverArray[i];
                    if (imudatareceiver_plus.g_quat_array[i].Count() > 0)
                    {
                        valueNumCount++;
                        longTimeNoData[i] = 0;
                    }
                }
                bool isOffLine = false;
                if (valueNumCount < totalNumber)
                {
                    for (int i = startIndex; i < endIndex; i++)
                    {
                        //imuDataReceiver_plus* imu_t = m_imuReceiverArray[i];
                        if (imudatareceiver_plus.g_quat_array[i].Count() <= 0)
                        {
                            longTimeNoData[i]++;
                        }
                        if (longTimeNoData[i] > 200)
                        {
                            isOffLine = true;
                        }
                    }
                    if (isOffLine == true)
                    {
                        //qDebug() << "传感器掉线！" << longTimeNoData[0] << longTimeNoData[1] << longTimeNoData[2] << longTimeNoData[3] << longTimeNoData[4] << longTimeNoData[5] << longTimeNoData[6];
                        Console.WriteLine("传感器掉线！" + longTimeNoData[0] + ' ' + longTimeNoData[1] + ' ' + longTimeNoData[2] + ' ' + longTimeNoData[3] + ' ' +
                                                           longTimeNoData[4] + ' ' + longTimeNoData[5] + ' ' + longTimeNoData[6] + ' ');
                    }
                }
                if (valueNumCount >= totalNumber)
                {
                    //确定最大值
                    //        bool isJump[7];
                    //        for(int i=startIndex; i<6; i++){
                    //            isJump[i] = false;
                    //        }
                    for (int i = startIndex; i < endIndex; i++)
                    {
                        //imuDataReceiver_plus* imu_t = m_imuReceiverArray[i];
                        if (wanzhengxing_array[i] == false)
                        {
                            ImuQuat imuquat = getAData(i);
                            if (imuquat.time != -999)
                            {

                                int softTime = imuquat.time - imudatareceiver_plus.m_currentTime[i];
                                //if (softTime - currentIndexMax > 60 * 60 * 100 || softTime - currentIndexMax < -60 * 60 * 100)
                                //{
                                //    //qDebug("数据有问题！");
                                //    Console.WriteLine("数据有问题！");
                                //    //踢掉
                                //    wanzhengxing_array[i] = false;
                                //    //qDebug() << "踢掉！" << "index: " << imu_t->m_index << "time" << softTime << oldCurrentIndex << currentIndexMax;
                                //    continue;
                                //}
                                if (softTime <= 24 && softTime >= 0)
                                {
                                    currentIndexMax = 0;
                                    oldCurrentIndex = 0;
                                    for (int iii = startIndex; iii < endIndex; iii++)
                                    {
                                        wanzhengxing_array[iii] = false;
                                    }
                                }
                                if (softTime - currentIndexMax > 5 * 100)
                                {
                                    //qDebug("数据有问题！超过10秒钟！");
                                    string msg = "数据有问题！超过5秒钟！ ";
                                    msg += ": " + i + " " + currentIndexMax.ToString() + " " + softTime;
                                    //Console.WriteLine(msg);
                                    //踢掉
                                    wanzhengxing_array[i] = false;
                                    //qDebug() << "踢掉！" << "index: " << imu_t->m_index << "time" << softTime << oldCurrentIndex << currentIndexMax;
                                    syncFailCountPositive[i]++;
                                    syncSuccessCount = 0;
                                    if (syncFailCountPositive[i] % 100 == 98)
                                    {
                                        //imudatareceiver_plus.syncTimeStamp();
                                        //踢掉-清空
                                        //int j = i;
                                        //if (i == 1)
                                        //{
                                        //    j = 4;
                                        //}
                                        //else if (i == 4)
                                        //{
                                        //    j = 1;
                                        //}
                                        //else
                                        //{
                                        //    j = i;
                                        //}
                                        oldCurrentIndex = currentIndexMax;
                                        currentIndexMax = softTime;
                                        for (int ii = startIndex; ii < endIndex; ii++)
                                        {
                                            wanzhengxing_array[ii] = false;
                                        }
                                        imuquat_array[i] = imuquat;
                                        wanzhengxing_array[i] = true;
                                        //qDebug() << "跳步！" << currentIndexMax << "index: " << imu_t->m_index << "time" << softTime;
                                        //Console.WriteLine("跳步！");
                                    }
                                    continue;
                                }
                                else if(softTime - currentIndexMax < -5 * 100)
                                {
                                    //qDebug("数据有问题！超过10秒钟！");
                                    string msg = "数据有问题！少于5秒钟！";
                                    msg += ": " + i + " " + currentIndexMax.ToString() + " " + softTime;
                                    //Console.WriteLine(msg);
                                    //踢掉
                                    wanzhengxing_array[i] = false;
                                    syncFailCountNegtive[i]++;
                                    syncSuccessCount = 0;
                                    if (syncFailCountNegtive[i] % 100 == 98)
                                    {
                                        Console.WriteLine("踢掉-清空！");
                                        for (int iiii = startIndex; iiii < endIndex; iiii++)
                                        {
                                            imudatareceiver_plus.g_quat_array[iiii].Clear();
                                            wanzhengxing_array[iiii] = false;
                                        }
                                        imudatareceiver_plus.syncTimeStamp();
                                    }
                                    //qDebug() << "踢掉！" << "index: " << imu_t->m_index << "time" << softTime << oldCurrentIndex << currentIndexMax;
                                    continue;
                                }

                                if (softTime >= 0)
                                {
                                    if (softTime < currentIndexMax - 60)
                                    {
                                        //踢掉-清空
                                        //int j = i;
                                        //if (i == 1)
                                        //{
                                        //    j = 4;
                                        //}
                                        //else if (i == 4)
                                        //{
                                        //    j = 1;
                                        //}
                                        //else
                                        //{
                                        //    j = i;
                                        //}

                                        if(tiaobuCount % 10 == 10-1)
                                        {
                                            Console.WriteLine("踢掉-清空！");
                                            for (int iiii = startIndex; iiii < endIndex; iiii++)
                                            {
                                                imudatareceiver_plus.g_quat_array[iiii].Clear();
                                                wanzhengxing_array[iiii] = false;
                                            }
                                        }
                                        
                                        //wanzhengxing_array[i] = false;
                                        //qDebug() << "踢掉-清空！" << "index: " << imu_t->m_index << "time" << softTime << oldCurrentIndex << currentIndexMax;
                                        
                                        syncSuccessCount = 0;
                                        tiaobuCount++;
                                        if(tiaobuCount % 100 == 98)
                                        {
                                            Console.WriteLine("踢掉-清空！");
                                            for (int iiii = startIndex; iiii < endIndex; iiii++)
                                            {
                                                imudatareceiver_plus.g_quat_array[iiii].Clear();
                                                wanzhengxing_array[iiii] = false;
                                            }
                                            imudatareceiver_plus.syncTimeStamp();
                                        }
                                        //存在一个bug，如果currentIndexMax太高，有个传感器的softTime太低
                                    }
                                    else if (softTime >= currentIndexMax - 60 && softTime < currentIndexMax)
                                    {
                                        //踢掉
                                        wanzhengxing_array[i] = false;
                                        //qDebug() << "踢掉！" << "index: " << imu_t->m_index << "time" << softTime << oldCurrentIndex << currentIndexMax;
                                        //Console.WriteLine("踢掉！");
                                    }
                                    else if (softTime == currentIndexMax)
                                    {
                                        imuquat_array[i] = imuquat;
                                        wanzhengxing_array[i] = true;
                                    }
                                    else if (softTime > currentIndexMax)
                                    {
                                        string msg = "跳步！";
                                        msg += ": " + i + " " + currentIndexMax.ToString() + " " + softTime + " " + (softTime - currentIndexMax);
                                        //Console.WriteLine(msg);

                                        longTimeSyncJumpCount[i] += (softTime - currentIndexMax);
                                        longTimeSyncJumpRecoverCount[i] = 0;
                                        oldCurrentIndex = currentIndexMax;
                                        currentIndexMax = softTime;
                                        for (int ii = startIndex; ii < endIndex; ii++)
                                        {
                                            wanzhengxing_array[ii] = false;
                                        }
                                        imuquat_array[i] = imuquat;
                                        wanzhengxing_array[i] = true;
                                        //qDebug() << "跳步！" << currentIndexMax << "index: " << imu_t->m_index << "time" << softTime;
                                        
                                    }
                                }
                            }
                            else
                            {
                                //qDebug() << "拿到-999的帧！" << "index: " << imu_t->m_index;
                                Console.WriteLine("拿到-999的帧！");
                            }
                        }
                    }
                    //qDebug() << "当前最大值： " << currentIndexMax << "完整bool: " << wanzhengxing_array[4] << wanzhengxing_array[5] << wanzhengxing_array[2] << wanzhengxing_array[3] ;
                    //if (currentIndexMax - oldCurrentIndex != 1)
                    //{
                    //    //qDebug() << "时间不符合！" << oldCurrentIndex << currentIndexMax;
                    //}

                    

                    //验证完整性
                    int wanzhengCount = 0;
                    int wanzhengxing_arrayCount = 0;
                    for (int i = startIndex; i < endIndex; i++)
                    {
                        //imuDataReceiver_plus* imu_t = m_imuReceiverArray[i];
                        if (wanzhengxing_array[i] == true && currentIndexMax == imuquat_array[i].time - imudatareceiver_plus.m_currentTime[i])
                        {
                            wanzhengCount++;
                        }
                        else
                        {
                            //qDebug() << "数据不完整！";
                            //Console.WriteLine("数据不完整！");
                        }

                        if (wanzhengxing_array[i] == true)
                        {
                            wanzhengxing_arrayCount++;
                        }
                    }
                    if(wanzhengCount < totalNumber && wanzhengxing_arrayCount == totalNumber)
                    {
                        Console.WriteLine("数据完整性异常！");
                        for (int i = startIndex; i < endIndex; i++)
                        {
                            wanzhengxing_array[i] = false;
                        }
                    }
                    if (wanzhengCount == totalNumber)
                    {

                        
                        //qDebug() << "已经完整！";
                        if (currentIndexMax - oldCurrentIndex == 1)
                        {
                            //qDebug() << "时间符合！" << oldCurrentIndex << currentIndexMax;
                            syncSuccessCount++;
                            if(syncSuccessCount % 100 == 99)
                            {
                                for (int ii = startIndex; ii < endIndex; ii++)
                                {
                                    syncFailCountNegtive[ii] = 0;
                                    syncFailCountPositive[ii] = 0;
                                    tiaobuCount = 0;
                                }
                            }
                            
                            for (int ii = startIndex; ii < endIndex; ii++)
                            {
                                longTimeSyncJumpRecoverCount[ii]++;
                                if (longTimeSyncJumpRecoverCount[ii] % 3000 == 3000 - 1)
                                {
                                    longTimeSyncJumpCount[ii] = 0;
                                }
                            }
                        }
                        //Console.WriteLine("已经完整！");
                        oldCurrentIndex = currentIndexMax;
                        longTimeNoSyncCount = 0;

                        lock (g_DATST_lockThis)
                        {
                            doCalculation();
                            float_array_t[4 * 7 + 3 * 7 + 3 * 7 ] = currentIndexMax;
                            m_oldTime = m_currentTime;
                            m_currentTime = currentIndexMax;
                            if (m_currentTime - m_oldTime > 1.5)
                            {
                                string msg = "帧时间：";
                                msg += " " + m_oldTime.ToString() + " " + m_currentTime + "差值 " + (m_currentTime - m_oldTime);
                                Console.WriteLine(msg);
                            }
                            //调用Action
                            if (onRecvFloat_array != null)
                            {
                                onRecvFloat_array(float_array_t);
                            }
                        }
                        currentIndexMax += 1;
                        for (int i = startIndex; i < endIndex; i++)
                        {
                            wanzhengxing_array[i] = false;
                        }
                    }
                }
                Thread.Sleep(1);
                longTimeNoSyncCount++;
            }

        }

        ImuQuat getAData(int i)
        {
            int num = imudatareceiver_plus.g_quat_array[i].Count();
            ImuQuat imuquatError = new ImuQuat();
            imuquatError.time = -999;
            if (num > 0)
            {
                ImuQuat imuquat = imudatareceiver_plus.g_quat_array[i][0];// 删除，并获取到它
                imudatareceiver_plus.g_quat_array[i].RemoveAt(0);
                if(imuquat == null)
                {
                    return imuquatError;
                }

                if (imuquat.time - old_stampTime[i] != 1 && imuquat.time - old_stampTime[i] != 0)
                {
                    //qDebug("index = %d AbsTime = %d old time = %d time delta = %d baseTime = %d softTime = %d",
                    //       imu_t->m_index, imuquat.time, old_stampTime[i], imuquat.time - old_stampTime[i], imu_t->m_currentTime, imuquat.time - imu_t->m_currentTime);
                    //string msg = "帧跳步 ";
                    //msg += "Queue Length: " + i + " " + imuquat.time.ToString() + " " + old_stampTime[i].ToString() + " " + (imuquat.time - old_stampTime[i]).ToString() + " " + imudatareceiver_plus.m_currentTime[i];
                    //Console.WriteLine(msg);
                }
                if (imuquat.time - imudatareceiver_plus.m_currentTime[i] == 49)
                {
                    //qDebug("index = %d AbsTime = %d time delta = %d baseTime = %d softTime = %d",
                    //       imu_t->m_index, imuquat.time, imuquat.time - old_stampTime[i], imu_t->m_currentTime, imuquat.time - imu_t->m_currentTime);
                    string msg = "帧起步 ";
                    msg += "Queue Length: " + i + " "  + (imuquat.time - imudatareceiver_plus.m_currentTime[i]).ToString() + " " + imudatareceiver_plus.m_currentTime[i];
                    Console.WriteLine(msg);
                    //Console.WriteLine("帧起步30");

                    for (int ii = 0; ii < 7; ii++)
                    {
                        longTimeSyncJumpCount[ii] = 0;
                    }
                }
                old_old_stampTime[i] = old_stampTime[i];
                old_stampTime[i] = imuquat.time;
                if (num > 20 && num <= 75)
                {
                    //qDebug() << "list too many: " << num << "index: " << imu_t->m_index;
                    //string msg = "list too many: ";
                    //msg += i + " " + num.ToString();
                    //Console.WriteLine(msg);
                }
                else if (num > 75)
                {
                    //qDebug() << "list too many and clear!" << num << "index: " << imu_t->m_index;
                    Console.WriteLine("list too many and clear!");
                    imudatareceiver_plus.g_quat_array[i].Clear();
                }
                return imuquat;
            }
            return imuquatError;
        }

        void doCalculation()
        {

            int valueNumCount = 0;
            int startIndex = 0;
            int endIndex = 7;
            int totalNumber = 7;
            for (int i = startIndex; i < endIndex; i++)
            {
                int tcpindex = 0;
                ImuQuat imuquat = imuquat_array[i];
                //string msg = "";
                //msg += "rot: " + imuquat.w.ToString() + " " + imuquat.x.ToString() + " " + imuquat.y.ToString() + " " + imuquat.z.ToString() + " " + imuquat.time.ToString() + " " + i + " " + (imuquat.time - imudatareceiver_plus.m_currentTime[i]);
                //Console.WriteLine(msg);

                //string msg = "";
                //msg += "rot: " + 
                //    imudatareceiver_plus._imuw_init[i].ToString() + " " + 
                //    imudatareceiver_plus._imux_init[i].ToString() + " " +
                //    imudatareceiver_plus._imuy_init[i].ToString() + " " + 
                //    imudatareceiver_plus._imuz_init[i].ToString() + " " + 
                //    imuquat.time.ToString() + " " + i + " " + (imuquat.time - imudatareceiver_plus.m_currentTime[i]);
                //Console.WriteLine(msg);

                int index = i;
                //if (i == 1)
                //{
                //    index = 4;
                //}
                //else if (i == 4)
                //{
                //    index = 1;
                //}
                //else
                //{
                //    index = i;
                //}
                imudatareceiver_plus._imuw[index] = imuquat.w; imudatareceiver_plus._imux[index] = imuquat.x; imudatareceiver_plus._imuy[index] = imuquat.y; imudatareceiver_plus._imuz[index] = imuquat.z;
                imudatareceiver_plus._gyrox[index] = imuquat.gyrox; imudatareceiver_plus._gyroy[index] = imuquat.gyroy; imudatareceiver_plus._gyroz[index] = imuquat.gyroz;
                imudatareceiver_plus._accx[index] = imuquat.accx; imudatareceiver_plus._accy[index] = imuquat.accy; imudatareceiver_plus._accz[index] = imuquat.accz;
                switch (index)
                {
                    case 0:
                        {
                            //腰部
                            //Matrix3d Rinit0 = Quaternion2RotationMatrix(_imux_init[index], _imuy_init[index], _imuz_init[index], _imuw_init[index]);
                            //Matrix3d Rnext0 = Quaternion2RotationMatrix(imuquat.x, imuquat.y, imuquat.z, imuquat.w);
                            //Matrix3d X0 = euler2RotationMatrix(_yao_Para - _angle0, 0, 0) * Rnext0 * Rinit0.adjoint() * euler2RotationMatrix(-_yao_Para + _angle0, 0, 0);
                            //Quaterniond Q0 = rotationMatrix2Quaterniond(X0);
                            Quat_t Rinit0 = new Quat_t(imudatareceiver_plus._imuw_init[index], -imudatareceiver_plus._imux_init[index], -imudatareceiver_plus._imuy_init[index], -imudatareceiver_plus._imuz_init[index]);
                            Quat_t Rnext0 = new Quat_t(imuquat.w, imuquat.x, imuquat.y, imuquat.z);
                            Quat_t euler2quat_front, euler2quat_rear;
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(imudatareceiver_plus.angle_Para[index] - imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_front);
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(-imudatareceiver_plus.angle_Para[index] + imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_rear);
                            Quat_t Q0, Q1, Q2, Q3;
                            imudatareceiver_plus.quat_pro_static(Rnext0, euler2quat_front, out Q1);
                            imudatareceiver_plus.quat_pro_static(Rinit0, Q1, out Q2);
                            imudatareceiver_plus.quat_pro_static(euler2quat_rear, Q2, out Q0);


                            tcpindex = 0;

                            float_array_t[4 * tcpindex + 0] = (float)Q0.x; float_array_t[4 * tcpindex + 1] = (float)Q0.y; float_array_t[4 * tcpindex + 2] = (float)Q0.z; float_array_t[4 * tcpindex + 3] = (float)Q0.w;
                            //float_array[4*tcpindex+0] = 0;float_array[4*tcpindex+1] = 0;float_array[4*tcpindex+2] = 0;float_array[4*tcpindex+3] = 1;
                            float_array_t[3 * tcpindex + 0 + 28] = imuquat.accx;
                            float_array_t[3 * tcpindex + 1 + 28] = imuquat.accy;
                            float_array_t[3 * tcpindex + 2 + 28] = imuquat.accz;
                            float_array_t[3 * tcpindex + 0 + 49] = imuquat.gyrox;
                            float_array_t[3 * tcpindex + 1 + 49] = imuquat.gyroy;
                            float_array_t[3 * tcpindex + 2 + 49] = imuquat.gyroz;
                            //gyroz[tcpindex] = imuquat.gyroz;
                            //float_array[3 * tcpindex + 2 + 49] = (float)m_delay[tcpindex] / 5.0;
                            //imuCurrentX[tcpindex] = (float)Q0.x; imuCurrentY[tcpindex] = (float)Q0.y; imuCurrentZ[tcpindex] = (float)Q0.z; imuCurrentW[tcpindex] = (float)Q0.w;
                            //string msg = "";
                            //msg += "rot: " + float_array_t[4 * tcpindex + 0].ToString() + " " + float_array_t[4 * tcpindex + 0].ToString() + " " + float_array_t[4 * tcpindex + 0].ToString() + " " + float_array_t[4 * tcpindex + 0].ToString() + " " + tcpindex.ToString();
                            //Console.WriteLine(msg);
                            break;
                        }
                    case 1:
                        {
                            //左大腿
                            //float angletL2 = _ldatuiPara - _angle1;
                            //float angletR2 = -_ldatuiPara + _angle1;
                            //Matrix3d R0L2 = euler2RotationMatrix(angletL2, 0, 0);
                            //Matrix3d R0R2 = euler2RotationMatrix(angletR2, 0, 0);
                            //Matrix3d Rinit1 = Quaternion2RotationMatrix(_imux_init[index], _imuy_init[index], _imuz_init[index], _imuw_init[index]);
                            //Matrix3d Rnext1 = Quaternion2RotationMatrix(imuquat.x, imuquat.y, imuquat.z, imuquat.w);
                            //Matrix3d X1 = R0L2 * Rnext1 * Rinit1.adjoint() * R0R2;
                            //Quaterniond Q1 = rotationMatrix2Quaterniond(X1);

                            Quat_t Rinit0 = new Quat_t(imudatareceiver_plus._imuw_init[index], -imudatareceiver_plus._imux_init[index], -imudatareceiver_plus._imuy_init[index], -imudatareceiver_plus._imuz_init[index]);
                            Quat_t Rnext0 = new Quat_t(imuquat.w, imuquat.x, imuquat.y, imuquat.z);
                            Quat_t euler2quat_front, euler2quat_rear;
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(imudatareceiver_plus.angle_Para[index] - imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_front);
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(-imudatareceiver_plus.angle_Para[index] + imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_rear);
                            Quat_t Q0, Q1, Q2, Q3;
                            imudatareceiver_plus.quat_pro_static(Rnext0, euler2quat_front, out Q1);
                            imudatareceiver_plus.quat_pro_static(Rinit0, Q1, out Q2);
                            imudatareceiver_plus.quat_pro_static(euler2quat_rear, Q2, out Q0);


                            tcpindex = 1;

                            float_array_t[4 * tcpindex + 0] = (float)Q0.x; float_array_t[4 * tcpindex + 1] = (float)Q0.y; float_array_t[4 * tcpindex + 2] = (float)Q0.z; float_array_t[4 * tcpindex + 3] = (float)Q0.w;
                            //float_array[4*tcpindex+0] = Q1.x();float_array[4*tcpindex+1] = Q1.y();float_array[4*tcpindex+2] = Q1.z();float_array[4*tcpindex+3] = Q1.w();
                            float_array_t[3 * tcpindex + 0 + 28] = imuquat.accx;
                            float_array_t[3 * tcpindex + 1 + 28] = imuquat.accy;
                            float_array_t[3 * tcpindex + 2 + 28] = imuquat.accz;
                            float_array_t[3 * tcpindex + 0 + 49] = imuquat.gyrox;
                            float_array_t[3 * tcpindex + 1 + 49] = imuquat.gyroy;
                            float_array_t[3 * tcpindex + 2 + 49] = imuquat.gyroz;
                            //float_array[3*tcpindex+2+49] = imuquat.gyroz;
                            //gyroz[tcpindex] = imuquat.gyroz;
                            //float_array[3 * tcpindex + 2 + 49] = (float)m_delay[tcpindex] / 5.0;
                            //imuCurrentX[tcpindex] = (float)Q0.x; imuCurrentY[tcpindex] = (float)Q0.y; imuCurrentZ[tcpindex] = (float)Q0.z; imuCurrentW[tcpindex] = (float)Q0.w;
                            break;
                        }
                    case 2:
                        {
                            //右大腿
                            //float angletL = _rdatuiPara - _angle4;
                            //float angletR = -_rdatuiPara + _angle4;
                            //Matrix3d R0L = euler2RotationMatrix(angletL, 0, 0);
                            //Matrix3d R0R = euler2RotationMatrix(angletR, 0, 0);
                            //Matrix3d Rinit4 = Quaternion2RotationMatrix(_imux_init[index], _imuy_init[index], _imuz_init[index], _imuw_init[index]);
                            //Matrix3d Rnext4 = Quaternion2RotationMatrix(imuquat.x, imuquat.y, imuquat.z, imuquat.w);
                            //Matrix3d X4 = R0L * Rnext4 * Rinit4.adjoint() * R0R;
                            //Quaterniond Q4 = rotationMatrix2Quaterniond(X4);

                            Quat_t Rinit0 = new Quat_t(imudatareceiver_plus._imuw_init[index], -imudatareceiver_plus._imux_init[index], -imudatareceiver_plus._imuy_init[index], -imudatareceiver_plus._imuz_init[index]);
                            Quat_t Rnext0 = new Quat_t(imuquat.w, imuquat.x, imuquat.y, imuquat.z);
                            Quat_t euler2quat_front, euler2quat_rear;
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(imudatareceiver_plus.angle_Para[index] - imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_front);
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(-imudatareceiver_plus.angle_Para[index] + imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_rear);
                            Quat_t Q0, Q1, Q2, Q3;
                            imudatareceiver_plus.quat_pro_static(Rnext0, euler2quat_front, out Q1);
                            imudatareceiver_plus.quat_pro_static(Rinit0, Q1, out Q2);
                            imudatareceiver_plus.quat_pro_static(euler2quat_rear, Q2, out Q0);


                            tcpindex = 2;
                            float_array_t[4 * tcpindex + 0] = (float)Q0.x; float_array_t[4 * tcpindex + 1] = (float)Q0.y; float_array_t[4 * tcpindex + 2] = (float)Q0.z; float_array_t[4 * tcpindex + 3] = (float)Q0.w;
                            //float_array[4*tcpindex+0] = Q4.x();float_array[4*tcpindex+1] = Q4.y();float_array[4*tcpindex+2] = Q4.z();float_array[4*tcpindex+3] = Q4.w();
                            float_array_t[3 * tcpindex + 0 + 28] = imuquat.accx;
                            float_array_t[3 * tcpindex + 1 + 28] = imuquat.accy;
                            float_array_t[3 * tcpindex + 2 + 28] = imuquat.accz;
                            float_array_t[3 * tcpindex + 0 + 49] = imuquat.gyrox;
                            float_array_t[3 * tcpindex + 1 + 49] = imuquat.gyroy;
                            float_array_t[3 * tcpindex + 2 + 49] = imuquat.gyroz;
                            //float_array[3*tcpindex+2+49] = imuquat.gyroz;
                            //gyroz[tcpindex] = imuquat.gyroz;
                            //float_array[3 * tcpindex + 2 + 49] = (float)m_delay[tcpindex] / 5.0;
                            //imuCurrentX[tcpindex] = (float)Q0.x; imuCurrentY[tcpindex] = (float)Q0.y; imuCurrentZ[tcpindex] = (float)Q0.z; imuCurrentW[tcpindex] = (float)Q0.w;
                            break;
                        }
                    case 3:
                        {
                            //左小腿
                            //Matrix3d Rinit2 = Quaternion2RotationMatrix(_imux_init[index], _imuy_init[index], _imuz_init[index], _imuw_init[index]);
                            //Matrix3d Rnext2 = Quaternion2RotationMatrix(imuquat.x, imuquat.y, imuquat.z, imuquat.w);
                            //Matrix3d X2 = euler2RotationMatrix(180 + _lxiaotuiPara - _angle2, 0, 0) * Rnext2 * Rinit2.adjoint() * euler2RotationMatrix(-180 - _lxiaotuiPara + _angle2, 0, 0);
                            //Quaterniond Q2 = rotationMatrix2Quaterniond(X2);

                            Quat_t Rinit0 = new Quat_t(imudatareceiver_plus._imuw_init[index], -imudatareceiver_plus._imux_init[index], -imudatareceiver_plus._imuy_init[index], -imudatareceiver_plus._imuz_init[index]);
                            Quat_t Rnext0 = new Quat_t(imuquat.w, imuquat.x, imuquat.y, imuquat.z);
                            Quat_t euler2quat_front, euler2quat_rear;
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(imudatareceiver_plus.angle_Para[index] - imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_front);
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(-imudatareceiver_plus.angle_Para[index] + imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_rear);
                            Quat_t Q0, Q1, Q2, Q3;
                            imudatareceiver_plus.quat_pro_static(Rnext0, euler2quat_front, out Q1);
                            imudatareceiver_plus.quat_pro_static(Rinit0, Q1, out Q2);
                            imudatareceiver_plus.quat_pro_static(euler2quat_rear, Q2, out Q0);

                            tcpindex = 3;
                            float_array_t[4 * tcpindex + 0] = (float)Q0.x; float_array_t[4 * tcpindex + 1] = (float)Q0.y; float_array_t[4 * tcpindex + 2] = (float)Q0.z; float_array_t[4 * tcpindex + 3] = (float)Q0.w;
                            //float_array[4*tcpindex+0] = Q2.x();float_array[4*tcpindex+1] = Q2.y();float_array[4*tcpindex+2] = Q2.z();float_array[4*tcpindex+3] = Q2.w();
                            float_array_t[3 * tcpindex + 0 + 28] = imuquat.accx;
                            float_array_t[3 * tcpindex + 1 + 28] = imuquat.accy;
                            float_array_t[3 * tcpindex + 2 + 28] = imuquat.accz;
                            float_array_t[3 * tcpindex + 0 + 49] = imuquat.gyrox;
                            float_array_t[3 * tcpindex + 1 + 49] = imuquat.gyroy;
                            float_array_t[3 * tcpindex + 2 + 49] = imuquat.gyroz;
                            //float_array[3*tcpindex+2+49] = imuquat.gyroz;
                            //gyroz[tcpindex] = imuquat.gyroz;
                            //float_array[3 * tcpindex + 2 + 49] = (float)m_delay[tcpindex] / 5.0;
                            //imuCurrentX[tcpindex] = (float)Q0.x; imuCurrentY[tcpindex] = (float)Q0.y; imuCurrentZ[tcpindex] = (float)Q0.z; imuCurrentW[tcpindex] = (float)Q0.w;
                            break;
                        }
                    case 4:
                        {
                            //右小腿
                            //Matrix3d Rinit5 = Quaternion2RotationMatrix(_imux_init[index], _imuy_init[index], _imuz_init[index], _imuw_init[index]);
                            //Matrix3d Rnext5 = Quaternion2RotationMatrix(imuquat.x, imuquat.y, imuquat.z, imuquat.w);
                            //Matrix3d X5 = euler2RotationMatrix(_rxiaotuiPara - _angle5, 0, 0) * Rnext5 * Rinit5.adjoint() * euler2RotationMatrix(-_rxiaotuiPara + _angle5, 0, 0);
                            //Quaterniond Q5 = rotationMatrix2Quaterniond(X5);

                            Quat_t Rinit0 = new Quat_t(imudatareceiver_plus._imuw_init[index], -imudatareceiver_plus._imux_init[index], -imudatareceiver_plus._imuy_init[index], -imudatareceiver_plus._imuz_init[index]);
                            Quat_t Rnext0 = new Quat_t(imuquat.w, imuquat.x, imuquat.y, imuquat.z);
                            Quat_t euler2quat_front, euler2quat_rear;
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(imudatareceiver_plus.angle_Para[index] - imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_front);
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(-imudatareceiver_plus.angle_Para[index] + imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_rear);
                            Quat_t Q0, Q1, Q2, Q3;
                            imudatareceiver_plus.quat_pro_static(Rnext0, euler2quat_front, out Q1);
                            imudatareceiver_plus.quat_pro_static(Rinit0, Q1, out Q2);
                            imudatareceiver_plus.quat_pro_static(euler2quat_rear, Q2, out Q0);

                            tcpindex = 4;
                            float_array_t[4 * tcpindex + 0] = (float)Q0.x; float_array_t[4 * tcpindex + 1] = (float)Q0.y; float_array_t[4 * tcpindex + 2] = (float)Q0.z; float_array_t[4 * tcpindex + 3] = (float)Q0.w;
                            //float_array[4*tcpindex+0] = Q5.x();float_array[4*tcpindex+1] = Q5.y();float_array[4*tcpindex+2] = Q5.z();float_array[4*tcpindex+3] = Q5.w();
                            float_array_t[3 * tcpindex + 0 + 28] = imuquat.accx;
                            float_array_t[3 * tcpindex + 1 + 28] = imuquat.accy;
                            float_array_t[3 * tcpindex + 2 + 28] = imuquat.accz;
                            float_array_t[3 * tcpindex + 0 + 49] = imuquat.gyrox;
                            float_array_t[3 * tcpindex + 1 + 49] = imuquat.gyroy;
                            float_array_t[3 * tcpindex + 2 + 49] = imuquat.gyroz;
                            //float_array[3*tcpindex+2+49] = imuquat.gyroz;
                            //gyroz[tcpindex] = imuquat.gyroz;
                            //float_array[3 * tcpindex + 2 + 49] = (float)m_delay[tcpindex] / 5.0;
                            //imuCurrentX[tcpindex] = (float)Q0.x; imuCurrentY[tcpindex] = (float)Q0.y; imuCurrentZ[tcpindex] = (float)Q0.z; imuCurrentW[tcpindex] = (float)Q0.w;
                            break;
                        }
                    case 5:
                        {
                            //左脚
                            //Matrix3d Rinit3 = Quaternion2RotationMatrix(_imux_init[index], _imuy_init[index], _imuz_init[index], _imuw_init[index]);
                            //Matrix3d Rnext3 = Quaternion2RotationMatrix(imuquat.x, imuquat.y, imuquat.z, imuquat.w);
                            //Matrix3d X3 = euler2RotationMatrix(_ljiaoPara - _angle3, 0, 0) * Rnext3 * Rinit3.adjoint() * euler2RotationMatrix(-_ljiaoPara + _angle3, 0, 0);
                            //Quaterniond Q3 = rotationMatrix2Quaterniond(X3);

                            Quat_t Rinit0 = new Quat_t(imudatareceiver_plus._imuw_init[index], -imudatareceiver_plus._imux_init[index], -imudatareceiver_plus._imuy_init[index], -imudatareceiver_plus._imuz_init[index]);
                            Quat_t Rnext0 = new Quat_t(imuquat.w, imuquat.x, imuquat.y, imuquat.z);
                            Quat_t euler2quat_front, euler2quat_rear;
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(imudatareceiver_plus.angle_Para[index] - imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_front);
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(-imudatareceiver_plus.angle_Para[index] + imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_rear);
                            Quat_t Q0, Q1, Q2, Q3;
                            imudatareceiver_plus.quat_pro_static(Rnext0, euler2quat_front, out Q1);
                            imudatareceiver_plus.quat_pro_static(Rinit0, Q1, out Q2);
                            imudatareceiver_plus.quat_pro_static(euler2quat_rear, Q2, out Q0);

                            tcpindex = 5;
                            float_array_t[4 * tcpindex + 0] = (float)Q0.x; float_array_t[4 * tcpindex + 1] = (float)Q0.y; float_array_t[4 * tcpindex + 2] = (float)Q0.z; float_array_t[4 * tcpindex + 3] = (float)Q0.w;
                            //float_array[4*tcpindex+0] = Q3.x();float_array[4*tcpindex+1] = Q3.y();float_array[4*tcpindex+2] = Q3.z();float_array[4*tcpindex+3] = Q3.w();
                            float_array_t[3 * tcpindex + 0 + 28] = imuquat.accx;
                            float_array_t[3 * tcpindex + 1 + 28] = imuquat.accy;
                            float_array_t[3 * tcpindex + 2 + 28] = imuquat.accz;
                            float_array_t[3 * tcpindex + 0 + 49] = imuquat.gyrox;
                            float_array_t[3 * tcpindex + 1 + 49] = imuquat.gyroy;
                            float_array_t[3 * tcpindex + 2 + 49] = imuquat.gyroz;
                            //float_array[3*tcpindex+2+49] = imuquat.gyroz;
                            //gyroz[tcpindex] = imuquat.gyroz;
                            //float_array[3 * tcpindex + 2 + 49] = (float)m_delay[tcpindex] / 5.0;
                            //imuCurrentX[tcpindex] = (float)Q0.x; imuCurrentY[tcpindex] = (float)Q0.y; imuCurrentZ[tcpindex] = (float)Q0.z; imuCurrentW[tcpindex] = (float)Q0.w;
                            break;
                        }
                    case 6:
                        {
                            //右脚
                            //Matrix3d Rinit6 = Quaternion2RotationMatrix(_imux_init[index], _imuy_init[index], _imuz_init[index], _imuw_init[index]);
                            //Matrix3d Rnext6 = Quaternion2RotationMatrix(imuquat.x, imuquat.y, imuquat.z, imuquat.w);
                            //Matrix3d X6 = euler2RotationMatrix(_rjiaoPara - _angle6, 0, 0) * Rnext6 * Rinit6.adjoint() * euler2RotationMatrix(-_rjiaoPara + _angle6, 0, 0);
                            //Quaterniond Q6 = rotationMatrix2Quaterniond(X6);

                            Quat_t Rinit0 = new Quat_t(imudatareceiver_plus._imuw_init[index], -imudatareceiver_plus._imux_init[index], -imudatareceiver_plus._imuy_init[index], -imudatareceiver_plus._imuz_init[index]);
                            Quat_t Rnext0 = new Quat_t(imuquat.w, imuquat.x, imuquat.y, imuquat.z);
                            Quat_t euler2quat_front, euler2quat_rear;
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(imudatareceiver_plus.angle_Para[index] - imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_front);
                            imudatareceiver_plus.Conversion_Euler_to_Quaternion_static(new Euler_t(-imudatareceiver_plus.angle_Para[index] + imudatareceiver_plus.angle_calibration[index], 0, 0), out euler2quat_rear);
                            Quat_t Q0, Q1, Q2, Q3;
                            imudatareceiver_plus.quat_pro_static(Rnext0, euler2quat_front, out Q1);
                            imudatareceiver_plus.quat_pro_static(Rinit0, Q1, out Q2);
                            imudatareceiver_plus.quat_pro_static(euler2quat_rear, Q2, out Q0);

                            tcpindex = 6;
                            float_array_t[4 * tcpindex + 0] = (float)Q0.x; float_array_t[4 * tcpindex + 1] = (float)Q0.y; float_array_t[4 * tcpindex + 2] = (float)Q0.z; float_array_t[4 * tcpindex + 3] = (float)Q0.w;
                            //float_array[4 * tcpindex + 0] = Q6.x(); float_array[4 * tcpindex + 1] = Q6.y(); float_array[4 * tcpindex + 2] = Q6.z(); float_array[4 * tcpindex + 3] = Q6.w();
                            float_array_t[3 * tcpindex + 0 + 28] = imuquat.accx;
                            float_array_t[3 * tcpindex + 1 + 28] = imuquat.accy;
                            float_array_t[3 * tcpindex + 2 + 28] = imuquat.accz;
                            float_array_t[3 * tcpindex + 0 + 49] = imuquat.gyrox;
                            float_array_t[3 * tcpindex + 1 + 49] = imuquat.gyroy;
                            float_array_t[3 * tcpindex + 2 + 49] = imuquat.gyroz;
                            //float_array[3*tcpindex+2+49] = imuquat.gyroz;
                            //gyroz[tcpindex] = imuquat.gyroz;
                            //float_array[3 * tcpindex + 2 + 49] = (float)m_delay[tcpindex] / 5.0;
                            //imuCurrentX[tcpindex] = (float)Q0.x; imuCurrentY[tcpindex] = (float)Q0.y; imuCurrentZ[tcpindex] = (float)Q0.z; imuCurrentW[tcpindex] = (float)Q0.w;
                            break;
                        }
                }
            }

            //if (mAniSocket0)
            //{
            //    //qDebug() << (float)m_delay[0] << (float)m_delay[1] << (float)m_delay[2] << (float)m_delay[3] << (float)m_delay[4] << (float)m_delay[5] << (float)m_delay[6];
            //    mAniSocket0->write((const char*)float_array_t, (4 * 7 + 3 * 7 + 3 * 7 + 1) * 4);
            //}

        }
    }

    public class hermesDLLVersion
    {
        public static String g_DLL_version = "2019091101";

        //获取DLL版本号
        public static String getDLLVersion()
        {
            return g_DLL_version;
        }

    }
 }
