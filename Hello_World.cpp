using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace BLHermesUDPAtom12_29
{
    public class Taidatui : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;
        public float _whichone;
        public int _doubleCount;

        public Taidatui()
        {
            _maxAngle = -1;
            _angle_zhunzhi = -1;
            _angle_zhun_count = -1;
            _angle_zhun_max = -1;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 0;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void ReqStandingSingleStraightLegRaise(float w, float x, float y, float z,
                                                                float w2, float x2, float y2, float z2,
                                                                float w3, float x3, float y3, float z3,
                                                                float w4, float x4, float y4, float z4,
                                                                float w5, float x5, float y5, float z5,
                                                                out float angle, out float anglepian, out float whichone)
        {
            angle = 0;
            anglepian = 0;
            whichone = -1;
            if (_maxAngle == -1)
            {
                return;
            }
            _doubleCount++;
            //---------------------左大腿 Datui Angle---------
            float datuiAngle_body = 90 - reqMainAngleRelative(w5, x5, y5, z5, 0, 1, 0, 0, 0, 2);
            float datuiAngle_zuo = reqMainAngleRelative(w, x, y, z, 2, 1, 0, 0, 0, 2);
            float datuiAngle_zuo_xiaotui = reqMainAngleRelative(w3, x3, y3, z3, 2, 1, 0, 0, 0, 2);
            float datuiAngle_zuo_wantui = reqMainAngleRelative(w, x, y, z, 2, w3, x3, y3, z3, 2);
            //---------------------右大腿 Datui Angle---------
            float datuiAngle_you = reqMainAngleRelative(w2, x2, y2, z2, 2, 1, 0, 0, 0, 2);
            float datuiAngle_you_xiaotui = reqMainAngleRelative(w4, x4, y4, z4, 2, 1, 0, 0, 0, 2);
            float datuiAngle_you_wantui = reqMainAngleRelative(w2, x2, y2, z2, 2, w4, x4, y4, z4, 2);
            float datuiAngle_yuo_li = reqMainAngleRelative(w, x, y, z, 2, w2, x2, y2, z2, 2);
            //---------------------左大腿 Pian Angle----------R0.adjoint()*R1

            Quat_t quat3 = new Quat_t(w5, x5, y5, z5);
            Quat_t quat0 = new Quat_t(w, x, y, z);
            Quat_t qzuo = new Quat_t(0, 0, 0, 0);
            reqRotationQuat(quat3, quat0, out qzuo);
            float angle_pian_zuo = reqPianAngle(qzuo);

            Quat_t quat2 = new Quat_t(w2, x2, y2, z2);
            Quat_t qyou = new Quat_t(0, 0, 0, 0);
            reqRotationQuat(quat3, quat2, out qyou);
            float angle_pian_you = reqPianAngle(qyou);

            //-----------------------------------------------
            float datuiAngle_com = -1; float angle_pian_com = -1;
            if (datuiAngle_zuo > datuiAngle_you)
            {
                datuiAngle_com = datuiAngle_zuo;
                angle_pian_com = angle_pian_zuo;
            }
            else
            {
                datuiAngle_com = datuiAngle_you;
                angle_pian_com = angle_pian_you;
            }


            if (datuiAngle_com > _maxAngle)
            {
                _maxAngle = datuiAngle_com;
            }
            _angle_pian = angle_pian_com;

            whichone = -1; _whichone = -1; float wantui_jian = 0; float wantui_jian_zuo = 0; float wantui_jian_you = 0;
            float datuiAngle_zuo_duli = reqMainAngleRelative(w, x, y, z, 2, 1, 0, 0, 0, 2);
            float datuiAngle_you_duli = reqMainAngleRelative(w2, x2, y2, z2, 2, 1, 0, 0, 0, 2);
            if ((datuiAngle_zuo_duli > 25 && datuiAngle_you_duli > 25) || (datuiAngle_zuo_wantui > 40 || datuiAngle_you_wantui > 40)) return;
            if (datuiAngle_zuo > datuiAngle_you)
            {
                if (Math.Abs(datuiAngle_zuo) > 25)
                {
                    _whichone = 0;
                }
            }
            else
            {
                if (Math.Abs(datuiAngle_you) > 25)
                {
                    _whichone = 1;
                }
            }

            if (Math.Abs(datuiAngle_you) <= 25 && Math.Abs(datuiAngle_zuo) <= 25)
            {
                if (_doubleCount % 2 == 1)
                    _whichone = 1;
                if (_doubleCount % 2 == 0)
                    _whichone = 0;
            }

            if (datuiAngle_you > 10 || datuiAngle_you < -10)
            {
                wantui_jian_zuo = Math.Abs(Math.Abs(datuiAngle_you) - 10.0F);
            }

            if (datuiAngle_zuo > 10 || datuiAngle_zuo < -10)
            {
                wantui_jian_you = Math.Abs(Math.Abs(datuiAngle_zuo) - 10.0F);
            }

            float yaodaichang = 0.0F;
            float daichangzhi = (datuiAngle_com / 30.0F - 1.0F) * 10.0F;
            if (datuiAngle_body >= -daichangzhi && datuiAngle_body <= daichangzhi) yaodaichang = 0;
            else if (datuiAngle_body > daichangzhi) yaodaichang = datuiAngle_body - daichangzhi;
            else if (datuiAngle_body < -daichangzhi) yaodaichang = datuiAngle_body + daichangzhi;

            float wantui_real_you = 0.0F; float wantui_real_zuo = 0.0F;
            if (datuiAngle_you_wantui > 15) wantui_real_you = datuiAngle_you_wantui - 15;
            else if (datuiAngle_you_wantui < 15) wantui_real_you = -(15 - datuiAngle_you_wantui);

            if (datuiAngle_zuo_wantui > 15) wantui_real_zuo = datuiAngle_zuo_wantui - 15;
            else if (datuiAngle_zuo_wantui < 15) wantui_real_zuo = -(15 - datuiAngle_zuo_wantui);

            if (maintainMaxAngle(datuiAngle_com, 25, zhixideltaAngle, zhixidelayCount) == 500)
            {
                if (datuiAngle_zuo > datuiAngle_you)
                {
                    if (Math.Abs(datuiAngle_zuo) > 25)
                    {
                        wantui_jian = wantui_jian_zuo;
                        whichone = 0;
                        angle = datuiAngle_zuo_xiaotui - wantui_real_you / 2.0F - yaodaichang;
                        anglepian = _angle_pian;
                        return;
                    }
                }
                else
                {
                    if (Math.Abs(datuiAngle_you) > 25)
                    {
                        wantui_jian = wantui_jian_you;
                        whichone = 1;
                        angle = datuiAngle_you_xiaotui - wantui_real_zuo / 2.0F - yaodaichang;
                        anglepian = _angle_pian;
                        return;
                    }
                }
            }

            angle = datuiAngle_yuo_li - yaodaichang - wantui_jian;
            anglepian = _angle_pian;
        }

        float maintainMaxAngle(float angle, float yuzhi, float delta, float count_final)
        {
            if (angle > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angle <= yuzhi)
            {
                _angle_zhun_count = 0;
                _angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                if (_angle_zhunzhi > _angle_zhun_max)
                {
                    _angle_zhun_max = _angle_zhunzhi;
                    return 500;
                }

            }
            return 0;
        }

        public float reqRateOfProcess(out int whichone)
        {
            whichone = (int)_whichone;
            return _angle_zhun_count / delayCount;
        }
    }

    public class Housheng : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;
        public float _whichone;
        public int _doubleCount;
        public float _houshengDaichang_left, _houshengDaichang_right;
        public float _houshengValue_left, _houshengValue_right;

        public Housheng()
        {
            _maxAngle = -1;
            _angle_zhunzhi = -1;
            _angle_zhun_count = -1;
            _angle_zhun_max = -1;
            _whichone = -1;
            _doubleCount = 0;
            _houshengDaichang_left = 0;
            _houshengDaichang_right = 0;
            _houshengValue_left = 0;
            _houshengValue_right = 0;
        }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 0;
            _whichone = -1;
            _doubleCount = 0;
            _houshengDaichang_left = 0;
            _houshengDaichang_right = 0;
            _houshengValue_left = 0;
            _houshengValue_right = 0;
        }

        public void ReqStandingSingleStraightLegRaise(float w, float x, float y, float z,
                                                                float w2, float x2, float y2, float z2,
                                                                float w3, float x3, float y3, float z3,
                                                                float w4, float x4, float y4, float z4,
                                                                float w5, float x5, float y5, float z5,
                                                                out float angle, out float anglepian, out float whichone)
        {
            angle = 0;
            anglepian = 0;
            whichone = -1;
            if (_maxAngle == -1)
            {
                return;
            }
            _doubleCount++;
            float angleLimited = 10;
            float daichang = 90 - reqMainAngleRelative(w3, x3, y3, z3, 1, 1, 0, 0, 0, 2);
            float yaobuDaichang = reqMainAngleRelative(w3, x3, y3, z3, 2, 1, 0, 0, 0, 2);
            //---------------------左大腿与腰 Pian Angle-------------------------------------R0.adjoint()*R1
            Quat_t quat3 = new Quat_t( w3, x3, y3, z3 );
            Quat_t quat0 = new Quat_t(w, x, y, z );
            Quat_t qzuo = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat3, quat0, out qzuo);
            float datuiAngle_zuo = reqMainAngle(w, x, y, z) - 88;
            float angle_pian_zuo = reqPianAngle(qzuo);
            //---------------------右大腿与腰---------------------------------------------
            Quat_t quat2 = new Quat_t(w2, x2, y2, z2 );
            Quat_t qyou = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat3, quat2, out qyou);
            float datuiAngle_you = reqMainAngle(w2, x2, y2, z2) - 88;
            float angle_pian_you = reqPianAngle(qyou);


            float datuiAngle_li_you = reqMainAngleRelative(w2, x2, y2, z2, 2, 1, 0, 0, 0, 2) - 90;
            float datuiAngle_li_zuo = reqMainAngleRelative(w, x, y, z, 2, 1, 0, 0, 0, 2) - 90;

            float datuiAngle_li_you2 = 180 - (180 - reqMainAngleRelative(w2, x2, y2, z2, 2, 1, 0, 0, 0, 2) + yaobuDaichang);
            float datuiAngle_li_zuo2 = 180 - (180 - reqMainAngleRelative(w, x, y, z, 2, 1, 0, 0, 0, 2) + yaobuDaichang);

            //-----------------------------------------------
            float datuiAngle_com = -1; float angle_pian_com = -1;
            if (datuiAngle_zuo > datuiAngle_you)
            {
                datuiAngle_com = datuiAngle_zuo;
                angle_pian_com = angle_pian_zuo;
            }
            else
            {
                datuiAngle_com = datuiAngle_you;
                angle_pian_com = angle_pian_you;
            }


            if (datuiAngle_com > _maxAngle)
            {
                _maxAngle = datuiAngle_com;
            }
            _angle_pian = angle_pian_com;

            if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) < 100) return;

            whichone = -1; _whichone = -1;
            if (datuiAngle_zuo > datuiAngle_you)
            {
                if (Math.Abs(datuiAngle_zuo) > angleLimited)
                {
                    if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 100)
                        _whichone = 0;
                }
            }
            else
            {
                if (Math.Abs(datuiAngle_you) > angleLimited)
                {
                    if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 100)
                        _whichone = 1;
                }
            }
            if (Math.Abs(datuiAngle_you) <= angleLimited && Math.Abs(datuiAngle_zuo) <= angleLimited)
            {
                if (_doubleCount % 2 == 1)
                    _whichone = 1;
                if (_doubleCount % 2 == 0)
                    _whichone = 0;
            }
            int count_t = (int)maintainMaxAngle(datuiAngle_com, angleLimited, houshengDelta, houshengCount);
            if (count_t == 499)
            {
                if (datuiAngle_zuo > datuiAngle_you)
                {
                    if (Math.Abs(datuiAngle_zuo) > angleLimited)
                    {
                        if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 100)
                        {
                            _houshengDaichang_left = daichang;
                        }
                    }
                }
                else
                {
                    if (Math.Abs(datuiAngle_you) > angleLimited)
                    {
                        if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 100)
                        {
                            _houshengDaichang_right = daichang;
                        }
                    }
                }
            }

            if (count_t == 500)
            {
                if (datuiAngle_zuo > datuiAngle_you)
                {
                    if (Math.Abs(datuiAngle_zuo) > angleLimited)
                    {
                        if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 100)
                        {
                            if (_houshengDaichang_right == 0)
                            {
                                angle = datuiAngle_li_zuo;
                                anglepian = _angle_pian;
                                whichone = 0;
                            }
                            _houshengValue_left = datuiAngle_li_zuo;
                            //_houshengValue_left = datuiAngle_li_zuo2;
                        }

                    }
                }
                else
                {
                    if (Math.Abs(datuiAngle_you) > angleLimited)
                    {
                        if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 100)
                        {
                            if (_houshengDaichang_left == 0)
                            {
                                angle = datuiAngle_li_you;
                                anglepian = _angle_pian;
                                whichone = 1;
                            }
                            _houshengValue_right = datuiAngle_li_you;
                            //_houshengValue_right = datuiAngle_li_you2;
  
                        }
                    }
                }
            }

            float PermitedAngle = 12.0F;
            if (count_t == 501)
            {
                if (datuiAngle_zuo > datuiAngle_you)
                {
                    if (Math.Abs(datuiAngle_zuo) > angleLimited)
                    {
                        if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 100)
                        {
                            if (_houshengDaichang_right == 0)
                            {
                                //do nothing!
                            }
                            else
                            {
                                float meanDaichang = (_houshengDaichang_left - _houshengDaichang_right) / 2.0F;
                                if (Math.Abs(meanDaichang) < PermitedAngle)
                                {
                                    angle = _houshengValue_left;
                                    if(angle < 5)
                                    {
                                        angle = 5;
                                    }
                                }
                                else
                                {
                                    angle = _houshengValue_left - Math.Abs(meanDaichang) * 0.5F + PermitedAngle * 0.5F;
                                    if (angle < 5)
                                    {
                                        angle = 5;
                                    }
                                }
                                anglepian = _angle_pian;
                                whichone = 0;
                            }
                        }
                    }
                }
                else
                {
                    if (Math.Abs(datuiAngle_you) > angleLimited)
                    {
                        if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 100)
                        {
                            if (_houshengDaichang_left == 0)
                            {
                                //do nothing!
                            }
                            else
                            {
                                float meanDaichang = (_houshengDaichang_left - _houshengDaichang_right) / 2.0F;
                                if (Math.Abs(meanDaichang) < PermitedAngle)
                                {
                                    angle = _houshengValue_left;
                                    if (angle < 5)
                                    {
                                        angle = 5;
                                    }
                                }
                                else
                                {
                                    angle = _houshengValue_left - Math.Abs(meanDaichang) * 0.5F + PermitedAngle * 0.5F;
                                    if (angle < 5)
                                    {
                                        angle = 5;
                                    }
                                }
                                anglepian = _angle_pian;
                                whichone = 0;
                            }

                        }
                    }
                }
            }


            if (count_t == 502)
            {
                if (datuiAngle_zuo > datuiAngle_you)
                {
                    if (Math.Abs(datuiAngle_zuo) > angleLimited)
                    {
                        if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 100)
                        {
                            if (_houshengDaichang_right == 0)
                            {
                                //do nothing!
                            }
                            else
                            {
                                float meanDaichang = (_houshengDaichang_left - _houshengDaichang_right) / 2.0F;
                                if (Math.Abs(meanDaichang) < PermitedAngle)
                                {
                                    angle = _houshengValue_right;
                                    if (angle < 5)
                                    {
                                        angle = 5;
                                    }
                                }
                                else
                                {
                                    angle = _houshengValue_right - Math.Abs(meanDaichang) * 0.5F + PermitedAngle * 0.5F;
                                    if (angle < 5)
                                    {
                                        angle = 5;
                                    }
                                }
                                anglepian = _angle_pian;
                                whichone = 1;
                            }
                        }
                    }
                }
                else
                {
                    if (Math.Abs(datuiAngle_you) > angleLimited)
                    {
                        if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 100)
                        {
                            if (_houshengDaichang_left == 0)
                            {
                                //do nothing!
                            }
                            else
                            {
                                float meanDaichang = (_houshengDaichang_left - _houshengDaichang_right) / 2.0F;
                                if (Math.Abs(meanDaichang) < PermitedAngle)
                                {
                                    angle = _houshengValue_right;
                                    if (angle < 5)
                                    {
                                        angle = 5;
                                    }
                                }
                                else
                                {
                                    angle = _houshengValue_right - Math.Abs(meanDaichang) * 0.5F + PermitedAngle * 0.5F;
                                    if (angle < 5)
                                    {
                                        angle = 5;
                                    }
                                }
                                anglepian = _angle_pian;
                                whichone = 1;
                            }

                        }
                    }
                }
            }
        }

        float maintainMaxAngle(float angle, float yuzhi, float delta, float count_final)
        {
            if (angle > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angle <= yuzhi)
            {
                _angle_zhun_count = 0;
                _angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                if (_angle_zhunzhi > _angle_zhun_max)
                {
                    _angle_zhun_max = _angle_zhunzhi;
                    return 500;
                }

            }
            if (_angle_zhun_count == count_final - 1)
            {
                return 499;
            }

            if (_angle_zhun_count == count_final + 1)
            {
                return 501;
            }
            if (_angle_zhun_count == count_final + 2)
            {
                return 502;
            }
            return 0;
        }

        public float reqRateOfProcess(out int whichone)
        {
            whichone = (int)_whichone;
            return _angle_zhun_count / houshengCount;
        }
    }

    public class Cetaidatui : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;
        public float _whichone;
        public int _doubleCount;

        public Cetaidatui()
        {
            _maxAngle = -1;
            _angle_zhunzhi = -1;
            _angle_zhun_count = -1;
            _angle_zhun_max = -1;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 0;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void ReqStandingSingleStraightLegRaise(float w, float x, float y, float z,
                                                                  float w2, float x2, float y2, float z2,
                                                                  float w3, float x3, float y3, float z3,
                                                                  out float angle, out float anglepian, out float whichone)
        {
            angle = 0;
            anglepian = 0;
            whichone = -1;
            if (_maxAngle == -1)
            {
                return;
            }
            //---------------------左大腿 Datui Angle---------
            float datuiAngle_body = reqMainAngle(w3, x3, y3, z3);
            float datuiAngle_zuo = reqMainAngle(w, x, y, z);

            //---------------------右大腿 Datui Angle---------
            float datuiAngle_you = reqMainAngle(w2, x2, y2, z2);

            //---------------------左大腿 Pian Angle----------R0.adjoint()*R1

            Quat_t quat3 = new Quat_t(w3, x3, y3, z3 );
            Quat_t quat0 = new Quat_t(w, x, y, z );
            Quat_t qzuo = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat3, quat0, out qzuo);
            float angle_pian_zuo = reqPianAngle(qzuo);

            Quat_t quat2 = new Quat_t(w2, x2, y2, z2 );
            Quat_t qyou = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat3, quat2, out qyou);
            float angle_pian_you = reqPianAngle(qyou);

            //-----------------------------------------------
            float datuiAngle_com = -1; float angle_pian_com = -1;
            if (datuiAngle_zuo > datuiAngle_you)
            {
                datuiAngle_com = datuiAngle_zuo;
                angle_pian_com = angle_pian_zuo;
            }
            else
            {
                datuiAngle_com = datuiAngle_you;
                angle_pian_com = angle_pian_you;
            }


            if (datuiAngle_com > _maxAngle)
            {
                _maxAngle = datuiAngle_com;
            }
            _angle_pian = angle_pian_com;



            whichone = -1;

            if (datuiAngle_zuo > 40 && datuiAngle_you > 40) return;

            if (datuiAngle_zuo > datuiAngle_you)
            {
                if (Math.Abs(datuiAngle_zuo) > 20)
                {
                    _whichone = 0;
                }
            }
            else
            {
                if (Math.Abs(datuiAngle_you) > 20)
                {
                    _whichone = 1;
                }
            }
            if (Math.Abs(datuiAngle_you) <= 20 && Math.Abs(datuiAngle_zuo) <= 20)
            {
                if (_doubleCount % 2 == 1)
                    _whichone = 1;
                if (_doubleCount % 2 == 0)
                    _whichone = 0;
            }

            if (maintainMaxAngle(datuiAngle_com, 20, waizhanDelta2, waizhancount2) == 500)
            {
                if (datuiAngle_zuo > datuiAngle_you)
                {
                    if (Math.Abs(datuiAngle_zuo) > 20)
                    {
                        whichone = 0;
                    }
                }
                else
                {
                    if (Math.Abs(datuiAngle_you) > 20)
                    {
                        whichone = 1;
                    }
                }
            }
            angle = _angle_zhun_max + 6 - datuiAngle_body;
            anglepian = _angle_pian;
        }

        float maintainMaxAngle(float angle, float yuzhi, float delta, float count_final)
        {
            if (angle > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angle <= yuzhi)
            {
                _angle_zhun_count = 0;
                _angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                if (_angle_zhunzhi > _angle_zhun_max)
                {
                    _angle_zhun_max = _angle_zhunzhi;
                    return 500;
                }

            }
            if (_angle_zhun_count == count_final + 1)
            {
                return 501;
            }
            return 0;
        }

        public float reqRateOfProcess(out int whichone)
        {
            whichone = (int)_whichone;
            return _angle_zhun_count / waizhancount2;
        }
    }

    public class Cetaidatui_zuozi : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;
        public float _whichone;
        public int _doubleCount;

        public Cetaidatui_zuozi()
        {
            _maxAngle = -1;
            _angle_zhunzhi = -1;
            _angle_zhun_count = -1;
            _angle_zhun_max = -1;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 0;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void ReqStandingSingleStraightLegRaise(float w, float x, float y, float z,
                                                      float w2, float x2, float y2, float z2,
                                                      float w3, float x3, float y3, float z3,
                                                      float w4, float x4, float y4, float z4,
                                                      float w5, float x5, float y5, float z5,
                                                      out float angle, out float anglepian, out float whichone)
        {
            angle = 0;
            anglepian = 0;
            whichone = -1;
            if (_maxAngle == -1)
            {
                return;
            }
            _doubleCount++;
            float[] nVector = new float[3];
            float[] nVector1 = new float[3];
            float[] nVector2 = new float[3];
            reqCrossProduct(w5, x5, y5, z5, 1, 1, 0, 0, 0, 2, out nVector);
            reqCrossProduct(1, 0, 0, 0, 2, w3, x3, y3, z3, 2, out nVector1);
            reqCrossProduct(w4, x4, y4, z4, 2, 1, 0, 0, 0, 2, out nVector2);
            //---------------------左大腿 Datui Angle---------
            //float datuiAngle_body = reqMainAngle(w3, x3, y3, z3);
            float datuiAngle_zuo = reqMainAngle(w, x, y, z);
            datuiAngle_zuo = reqMainAngleRelative(w, x, y, z, 2, w2, x2, y2, z2, 2) / 2.0F;
            float datuiAngle_zuo_final = 90 - reqMainAngleRelativeEXBoth(nVector[0], nVector[1], nVector[2], nVector1[0], nVector1[1], nVector1[2]);

            //---------------------右大腿 Datui Angle---------
            float datuiAngle_you = reqMainAngle(w2, x2, y2, z2);
            datuiAngle_you = reqMainAngleRelative(w, x, y, z, 2, w2, x2, y2, z2, 2) / 2.0F;
            float datuiAngle_you_final = 90 - reqMainAngleRelativeEXBoth(nVector[0], nVector[1], nVector[2], nVector2[0], nVector2[1], nVector2[2]);

            float datuiAngle_zuo_final2 = reqMainAngleRelativeEXBoth(nVector2[0], nVector2[1], nVector2[2], nVector1[0], nVector1[1], nVector1[2]);
            //float datuiAngle_you_final2 = reqMainAngleRelativeEXBoth(nVector2[0], nVector2[1], nVector2[2], nVector1[0], nVector1[1], nVector1[2]);


            if (Math.Abs(datuiAngle_zuo_final - datuiAngle_you_final) >= 4)
            {
                float delta = Math.Abs(datuiAngle_zuo_final - datuiAngle_you_final) - 2;
                if (datuiAngle_zuo_final > datuiAngle_you_final)
                {
                    datuiAngle_zuo_final = datuiAngle_zuo_final - delta / 2.0F;
                    datuiAngle_you_final = datuiAngle_you_final + delta / 2.0F;
                }
                else
                {
                    datuiAngle_zuo_final = datuiAngle_zuo_final + delta / 2.0F;
                    datuiAngle_you_final = datuiAngle_you_final - delta / 2.0F;
                }
            }


            //---------------------左大腿 Pian Angle----------R0.adjoint()*R1

            Quat_t quat3 = new Quat_t(w5, x5, y5, z5);
            Quat_t quat0 = new Quat_t(w, x, y, z );
            Quat_t qzuo = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat3, quat0, out qzuo);
            float angle_pian_zuo = reqPianAngle(qzuo);

            Quat_t quat2 = new Quat_t(w2, x2, y2, z2 );
            Quat_t qyou = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat3, quat2, out qyou);
            float angle_pian_you = reqPianAngle(qyou);

            //-----------------------------------------------
            float datuiAngle_com = -1; float angle_pian_com = -1;
            if (datuiAngle_zuo > datuiAngle_you)
            {
                datuiAngle_com = datuiAngle_zuo;
                angle_pian_com = angle_pian_zuo;
            }
            else
            {
                datuiAngle_com = datuiAngle_you;
                angle_pian_com = angle_pian_you;
            }


            if (datuiAngle_com > _maxAngle)
            {
                _maxAngle = datuiAngle_com;
            }
            _angle_pian = angle_pian_com;



            whichone = -1; _whichone = -1;

            float datuiAngle_zuo_duli = reqMainAngleRelative(w, x, y, z, 2, 1, 0, 0, 0, 2);
            float datuiAngle_you_duli = reqMainAngleRelative(w2, x2, y2, z2, 2, 1, 0, 0, 0, 2);
            float datuiAngle_zuo_xigai = reqMainAngleRelative(w, x, y, z, 2, w3, x3, y3, z3, 2);
            float datuiAngle_you_xigai = reqMainAngleRelative(w2, x2, y2, z2, 2, w4, x4, y4, z4, 2);
            if (datuiAngle_zuo_duli < 70 || datuiAngle_you_duli < 70 || datuiAngle_zuo_xigai > 25 || datuiAngle_you_xigai > 25 || (datuiAngle_zuo_final + datuiAngle_you_final) < 35) return;

            if (Math.Abs(datuiAngle_zuo_final) > 20 && _doubleCount % 2 == 0)
            {
                _whichone = 0;
            }
            if (Math.Abs(datuiAngle_you_final) > 20 && _doubleCount % 2 == 1)
            {
                _whichone = 1;
            }

            if (Math.Abs(datuiAngle_you_final) <= 20 && Math.Abs(datuiAngle_zuo_final) <= 20)
            {
                if (_doubleCount % 2 == 1)
                    _whichone = 1;
                if (_doubleCount % 2 == 0)
                    _whichone = 0;
            }

            float value = maintainMaxAngle(datuiAngle_com, 1, waizhanDelta, waizhancount);

            if (value == 500)
            {
                if (Math.Abs(datuiAngle_zuo_final) > 15)
                {
                    whichone = 0;
                    angle = datuiAngle_zuo_final;
                    anglepian = _angle_pian;
                    return;
                }
            }
            if (value == 501)
            {
                if (Math.Abs(datuiAngle_you_final) > 15)
                {
                    whichone = 1;
                    angle = datuiAngle_you_final;
                    anglepian = _angle_pian;
                    return;
                }
            }
            angle = _angle_zhun_max;
            anglepian = _angle_pian;
        }

        float maintainMaxAngle(float angle, float yuzhi, float delta, float count_final)
        {
            if (angle > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angle <= yuzhi)
            {
                _angle_zhun_count = 0;
                _angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                if (_angle_zhunzhi > _angle_zhun_max)
                {
                    _angle_zhun_max = _angle_zhunzhi;
                    return 500;
                }

            }
            if (_angle_zhun_count == count_final + 1)
            {
                return 501;
            }
            return 0;
        }

        public float reqRateOfProcess(out int whichone)
        {
            whichone = (int)_whichone;
            return _angle_zhun_count / waizhancount;
        }
    }

    public class Gaotaitui : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;
        public float _whichone;
        public int _doubleCount;
        public Gaotaitui()
        {
            _maxAngle = -1;
            _angle_zhunzhi = -1;
            _angle_zhun_count = -1;
            _angle_zhun_max = -1;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 0;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void ReqStandingSingleStraightLegRaise(float w, float x, float y, float z,
                                                                 float w2, float x2, float y2, float z2,
                                                                 float w3, float x3, float y3, float z3,
                                                                 float w4, float x4, float y4, float z4,
                                                                 out float angle, out float anglepian, out float whichone)
        {
            angle = 0;
            anglepian = 0;
            whichone = -1;
            if (_maxAngle == -1)
            {
                return;
            }
            _doubleCount++;
            //---------------------左大腿与腰部 Datui Angle-----------
            float datuiAngle_body = reqMainAngle(w2, x2, y2, z2);
            Quat_t quat2 = new Quat_t( w2, x2, y2, z2 );
            Quat_t quat1 = new Quat_t( w, x, y, z );
            Quat_t qzuo = new Quat_t( 0, 0, 0, 0 );
            reqRotationQuat(quat2, quat1, out qzuo);
            float datuiAngle_zuo = reqMainAngle(w, x, y, z);
            datuiAngle_zuo = reqMainAngleRelative(w, x, y, z, 2, w2, x2, y2, z2, 2);

            //---------------------右大腿与腰部 Datui Angle-----------
            Quat_t quat4 = new Quat_t( w4, x4, y4, z4 );
            Quat_t quat3 = new Quat_t( w3, x3, y3, z3 );
            Quat_t qyou = new Quat_t( 0, 0, 0, 0 );
            reqRotationQuat(quat2, quat3, out qyou);
            float datuiAngle_you = reqMainAngle(w3, x3, y3, z3);
            datuiAngle_you = reqMainAngleRelative(w3, x3, y3, z3, 2, w4, x4, y4, z4, 2);

            //---------------------左大腿 Pian Angle------------
            float angle_pian_zuo = reqPianAngle(qzuo);

            //---------------------右大腿 Pian Angle------------
            float angle_pian_you = reqPianAngle(qyou);

            //-------------------------------------------------
            float datuiAngle_com = -1; float angle_pian_com = -1;
            if (datuiAngle_zuo > datuiAngle_you)
            {
                datuiAngle_com = datuiAngle_zuo;
                angle_pian_com = angle_pian_zuo;
            }
            else
            {
                datuiAngle_com = datuiAngle_you;
                angle_pian_com = angle_pian_you;
            }


            if (datuiAngle_com > _maxAngle)
            {
                _maxAngle = datuiAngle_com;
            }
            _angle_pian = angle_pian_com;

            whichone = -1; _whichone = -1;
            if (datuiAngle_zuo > datuiAngle_you)
            {
                if (Math.Abs(datuiAngle_zuo) > 35)
                {
                    _whichone = 0;
                }
            }
            else
            {
                if (Math.Abs(datuiAngle_you) > 35)
                {
                    _whichone = 1;
                }
            }
            if (Math.Abs(datuiAngle_you) <= 35 && Math.Abs(datuiAngle_zuo) <= 35)
            {
                if (_doubleCount % 2 == 1)
                    _whichone = 1;
                if (_doubleCount % 2 == 0)
                    _whichone = 0;
            }
            if (maintainMaxAngle(datuiAngle_com, 35, deltaAngle, gaotaituiCount) == 500)
            {
                if (datuiAngle_zuo > datuiAngle_you)
                {
                    if (Math.Abs(datuiAngle_zuo) > 35)
                    {
                        whichone = 0;
                    }
                }
                else
                {
                    if (Math.Abs(datuiAngle_you) > 35)
                    {
                        whichone = 1;
                    }
                }
            }
            float angleee = _angle_zhun_max;
            if (_angle_zhun_max < 95) angleee = 95.5F;
            angle = angleee;
            anglepian = _angle_pian;
        }

        float maintainMaxAngle(float angle, float yuzhi, float delta, float count_final)
        {
            if (angle > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angle <= yuzhi)
            {
                _angle_zhun_count = 0;
                _angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                if (_angle_zhunzhi > _angle_zhun_max)
                {
                    _angle_zhun_max = _angle_zhunzhi;
                    return 500;
                }

            }
            return 0;
        }

        public float reqRateOfProcess(out int whichone)
        {
            whichone = (int)_whichone;
            return _angle_zhun_count / gaotaituiCount;
        }
    }

    public class Houtaitui : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;
        public float _whichone;
        public int _doubleCount;

        public Houtaitui()
        {
            _maxAngle = -1;
            _angle_zhunzhi = -1;
            _angle_zhun_count = -1;
            _angle_zhun_max = -1;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 0;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void ReqStandingSingleStraightLegRaise(float w, float x, float y, float z,
                                                      float w2, float x2, float y2, float z2,
                                                      float w3, float x3, float y3, float z3,
                                                      float w4, float x4, float y4, float z4,
                                                      out float angle, out float anglepian, out float whichone)
        {
            angle = 0;
            anglepian = 0;
            whichone = -1;
            if (_maxAngle == -1)
            {
                return;
            }
            _doubleCount++;
            //---------------------左大腿与左小腿 Datui Angle-----------
            Quat_t quat2 = new Quat_t( w2, x2, y2, z2 );
            Quat_t quat1 = new Quat_t(w, x, y, z );
            Quat_t qzuo = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat1, quat2, out qzuo);
            float datuiAngle_zuo = reqMainAngle((float)qzuo.w, (float)qzuo.x, (float)qzuo.y, (float)qzuo.z);
            datuiAngle_zuo = reqMainAngleRelative(w, x, y, z, 2, w2, x2, y2, z2, 2);


            //---------------------右大腿与右小腿 Datui Angle-----------
            Quat_t quat4 = new Quat_t(w4, x4, y4, z4 );
            Quat_t quat3 = new Quat_t(w3, x3, y3, z3 );
            Quat_t qyou = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat3, quat4, out qyou);
            float datuiAngle_you = reqMainAngle((float)qyou.w, (float)qyou.x, (float)qyou.y, (float)qyou.z);
            datuiAngle_you = reqMainAngleRelative(w3, x3, y3, z3, 2, w4, x4, y4, z4, 2);

            //---------------------左大腿 Pian Angle------------
            float angle_pian_zuo = reqPianAngle(qzuo);

            //---------------------右大腿 Pian Angle------------
            float angle_pian_you = reqPianAngle(qyou);

            //-------------------------------------------------
            float datuiAngle_com = -1; float angle_pian_com = -1;
            if (datuiAngle_zuo > datuiAngle_you)
            {
                datuiAngle_com = datuiAngle_zuo;
                angle_pian_com = angle_pian_zuo;
            }
            else
            {
                datuiAngle_com = datuiAngle_you;
                angle_pian_com = angle_pian_you;
            }


            if (datuiAngle_com > _maxAngle)
            {
                _maxAngle = datuiAngle_com;
            }
            _angle_pian = angle_pian_com;

            whichone = -1; _whichone = -1;
            if (datuiAngle_zuo > datuiAngle_you)
            {
                if (Math.Abs(datuiAngle_zuo) > 65)
                {
                    _whichone = 0;
                }
            }
            else
            {
                if (Math.Abs(datuiAngle_you) > 65)
                {
                    _whichone = 1;
                }
            }
            if (Math.Abs(datuiAngle_you) <= 65 && Math.Abs(datuiAngle_zuo) <= 65)
            {
                if (_doubleCount % 2 == 1)
                    _whichone = 1;
                if (_doubleCount % 2 == 0)
                    _whichone = 0;
            }
            if (maintainMaxAngle(datuiAngle_com, 65, deltaAngle, delayCount) == 500)
            {
                if (datuiAngle_zuo > datuiAngle_you)
                {
                    if (Math.Abs(datuiAngle_zuo) > 65)
                    {
                        if (reqMainAngleRelativeSinXZ(w3, x3, y3, z3, 1, 0, 0, 0) > 65)
                            whichone = 0;
                    }
                }
                else
                {
                    if (Math.Abs(datuiAngle_you) > 65)
                    {
                        if (reqMainAngleRelativeSinXZ(w, x, y, z, 1, 0, 0, 0) > 65)
                            whichone = 1;
                    }
                }
            }
            angle = _angle_zhun_max - 10;
            anglepian = _angle_pian;
        }

        float maintainMaxAngle(float angle, float yuzhi, float delta, float count_final)
        {
            if (angle > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angle <= yuzhi)
            {
                _angle_zhun_count = 0;
                _angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                if (_angle_zhunzhi > _angle_zhun_max)
                {
                    _angle_zhun_max = _angle_zhunzhi;
                    return 500;
                }

            }
            return 0;
        }

        public float reqRateOfProcess(out int whichone)
        {
            whichone = (int)_whichone;
            return _angle_zhun_count / delayCount;
        }
    }

    public class Xiadunzuo : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;
        public Xiadunzuo()
        {
            _maxAngle = -1;
            _angle_zhunzhi = -1;
            _angle_zhun_count = -1;
            _angle_zhun_max = -1;
        }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 1000;
        }

        public void ReqStandingSingleStraightLegRaisezuo(float w, float x, float y, float z,
                                                         float w2, float x2, float y2, float z2,
                                                         out float angle, out float anglepian)
        {
            angle = 1000;
            anglepian = 0;
            if (_maxAngle == -1)
            {
                return;
            }
            //---------------------左小腿与左脚 Datui Angle-----------
            Quat_t quat2 = new Quat_t( w2, x2, y2, z2 );
            Quat_t quat1 = new Quat_t(w, x, y, z );
            Quat_t qzuo = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat1, quat2, out qzuo);
            float datuiAngle_zuo = reqMainAnglejiao((float)qzuo.w, (float)qzuo.x, (float)qzuo.y, (float)qzuo.z);
            datuiAngle_zuo = Math.Abs(reqMainAngleRelative(w, x, y, z, 2, w2, x2, y2, z2, 0) - 90);

            //---------------------左小腿与左脚 Pian Angle------------
            float angle_pian_zuo = reqPianAnglejiao(qzuo);

            //-------------------------------------------------

            if (datuiAngle_zuo > _maxAngle)
            {
                _maxAngle = datuiAngle_zuo;

            }
            _angle_pian = angle_pian_zuo;

            if (maintainMaxAngle(datuiAngle_zuo, 14, deltaAngle, delayCount) == 500)
            {
                if (90 - _angle_zhun_max > 15 && 90 - _angle_zhun_max < 80)
                {
                    angle = 90 - _angle_zhun_max + 10;
                }
            }
            anglepian = _angle_pian;
        }

        float maintainMaxAngle(float angle, float yuzhi, float delta, float count_final)
        {
            if (angle > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angle <= yuzhi)
            {
                _angle_zhun_count = 0;
                //_angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                _angle_zhun_max = 0;
                if (_angle_zhunzhi > _angle_zhun_max)
                {
                    _angle_zhun_max = _angle_zhunzhi;
                    return 500;
                }

            }
            return 0;
        }

        public float reqRateOfProcess()
        {
            return _angle_zhun_count / delayCount;
        }
    }

    public class Xiadunyou : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;
        public Xiadunyou()
        {
            _maxAngle = -1;
            _angle_zhunzhi = -1;
            _angle_zhun_count = -1;
            _angle_zhun_max = -1;
        }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 1000;
        }

        public void ReqStandingSingleStraightLegRaiseyou(float w, float x, float y, float z,
                                                         float w2, float x2, float y2, float z2,
                                                         out float angle, out float anglepian)
        {
            angle = 1000;
            anglepian = 0;
            if (_maxAngle == -1)
            {
                return;
            }
            //---------------------左小腿与左脚 Datui Angle-----------
            Quat_t quat2 = new Quat_t(w2, x2, y2, z2);
            Quat_t quat1 = new Quat_t(w, x, y, z);
            Quat_t qzuo = new Quat_t(0, 0, 0, 0);
            reqRotationQuat(quat1, quat2, out qzuo);
            float datuiAngle_zuo = reqMainAnglejiao((float)qzuo.w, (float)qzuo.x, (float)qzuo.y, (float)qzuo.z);
            datuiAngle_zuo = Math.Abs(reqMainAngleRelative(w, x, y, z, 2, w2, x2, y2, z2, 0) - 90);

            //---------------------左小腿与左脚 Pian Angle------------
            float angle_pian_zuo = reqPianAnglejiao(qzuo);

            //-------------------------------------------------

            if (datuiAngle_zuo > _maxAngle)
            {
                _maxAngle = datuiAngle_zuo;

            }
            _angle_pian = angle_pian_zuo;

            if (maintainMaxAngle(datuiAngle_zuo, 14, deltaAngle, delayCount) == 500)
            {
                if (90 - _angle_zhun_max > 15 && 90 - _angle_zhun_max < 80)
                {
                    angle = 90 - _angle_zhun_max + 10;
                }
            }
            anglepian = _angle_pian;
        }

        float maintainMaxAngle(float angle, float yuzhi, float delta, float count_final)
        {
            if (angle > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angle <= yuzhi)
            {
                _angle_zhun_count = 0;
                //_angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                _angle_zhun_max = 0;
                if (_angle_zhunzhi > _angle_zhun_max)
                {
                    _angle_zhun_max = _angle_zhunzhi;
                    return 500;
                }

            }
            return 0;
        }

        public float reqRateOfProcess()
        {
            return _angle_zhun_count / delayCount;
        }
    }

    public class Hexinzuo : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;

        public Hexinzuo()
	    {
		    _maxAngle = -1;
		    _angle_zhunzhi = -1;
		    _angle_zhun_count = -1;
		    _angle_zhun_max = -1;
	    }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 1000;
        }

        public void ReqStandingSingleStraightLegRaisezuo(float w, float x, float y, float z,
                                                         float w2, float x2, float y2, float z2,
                                                         float w3, float x3, float y3, float z3,
                                                         out float angle, out float anglepian)
        {
            angle = 1000;
            anglepian = 0;
            if (_maxAngle == -1)
            {
                return;
            }
            //---------------------左大腿与腰部 Datui Angle-----------
            Quat_t quat1 = new Quat_t ( w, x, y, z );
            Quat_t quat2 = new Quat_t ( w2, x2, y2, z2 );
            Quat_t qzuo = new Quat_t ( 0, 0, 0, 0 );
            reqRotationQuat(quat1, quat2, out qzuo);
            float datuiAngle_zuo = 180 - (-reqMainAngleRelative(w, x, y, z, 2, 1, 0, 0, 0, 2) + 180 + reqMainAngleRelative(w2, x2, y2, z2, 2, 1, 0, 0, 0, 2));
            float datuiAngle_dimian = reqMainAngle(w, x, y, z);

            //---------------------左大腿 Pian Angle------------
            float angle_pian_zuo = reqPianAngle(qzuo);

            //-------------------------------------------------
            if (datuiAngle_zuo > _maxAngle)
            {
                _maxAngle = datuiAngle_zuo;

            }
            _angle_pian = angle_pian_zuo;

            float xigai_angle = reqMainAngleRelative(w, x, y, z, 2, w3, x3, y3, z3, 2);
            if (xigai_angle > 30) return;

            if (maintainMaxAngle(datuiAngle_zuo, datuiAngle_dimian, 100, HexinDelta, HexinCount) == 500)
            {
                angle = _angle_zhun_max - 8 + 10;
            }
            anglepian = _angle_pian;
        }

        float maintainMaxAngle(float angle, float angleFuzhu, float yuzhi, float delta, float count_final)
        {
            if (angleFuzhu > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angleFuzhu <= yuzhi)
            {
                _angle_zhun_count = 0;
                //_angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                _angle_zhun_max = _angle_zhunzhi;
                return 500;

            }
            return 0;
        }

        public float reqRateOfProcess()
        {
            return _angle_zhun_count / HexinCount;
        }
    }

    public class Hexinyuo : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;

        public Hexinyuo()
        {
            _maxAngle = -1;
            _angle_zhunzhi = -1;
            _angle_zhun_count = -1;
            _angle_zhun_max = -1;
        }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 1000;
        }

        public void ReqStandingSingleStraightLegRaiseyou(float w, float x, float y, float z,
                                                         float w2, float x2, float y2, float z2,
                                                         float w3, float x3, float y3, float z3,
                                                         out float angle, out float anglepian)
        {
            angle = 1000;
            anglepian = 0;
            if (_maxAngle == -1)
            {
                return;
            }
            //---------------------左大腿与腰部 Datui Angle-----------
            Quat_t quat1 = new Quat_t(w, x, y, z);
            Quat_t quat2 = new Quat_t(w2, x2, y2, z2);
            Quat_t qzuo = new Quat_t(0, 0, 0, 0);
            reqRotationQuat(quat1, quat2, out qzuo);
            float datuiAngle_zuo = 180 - (-reqMainAngleRelative(w, x, y, z, 2, 1, 0, 0, 0, 2) + 180 + reqMainAngleRelative(w2, x2, y2, z2, 2, 1, 0, 0, 0, 2));
            float datuiAngle_dimian = reqMainAngle(w, x, y, z);

            //---------------------左大腿 Pian Angle------------
            float angle_pian_zuo = reqPianAngle(qzuo);

            //-------------------------------------------------
            if (datuiAngle_zuo > _maxAngle)
            {
                _maxAngle = datuiAngle_zuo;

            }
            _angle_pian = angle_pian_zuo;

            float xigai_angle = reqMainAngleRelative(w, x, y, z, 2, w3, x3, y3, z3, 2);
            if (xigai_angle > 30) return;

            if (maintainMaxAngle(datuiAngle_zuo, datuiAngle_dimian, 100, HexinDelta, HexinCount) == 500)
            {
                angle = _angle_zhun_max - 8 + 10;
            }
            anglepian = _angle_pian;
        }

        float maintainMaxAngle(float angle, float angleFuzhu, float yuzhi, float delta, float count_final)
        {
            if (angleFuzhu > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angleFuzhu <= yuzhi)
            {
                _angle_zhun_count = 0;
                //_angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                _angle_zhun_max = _angle_zhunzhi;
                return 500;

            }
            return 0;
        }

        public float reqRateOfProcess()
        {
            return _angle_zhun_count / HexinCount;
        }
    }

    public class Zubeiqu : RomBase
    {
        public float _maxAngle;
        public float _angle_pian;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;
        public float _whichone;
        public int _doubleCount;

        public Zubeiqu()
	    {
		    _maxAngle = -1;
		    _angle_zhunzhi = -1;
		    _angle_zhun_count = -1;
		    _angle_zhun_max = -1;
		    _whichone = -1;
		    _doubleCount = 0;
	    }

        public void resetLegRaiseAngle()
        {
            _maxAngle = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 0;
            _whichone = -1;
            _doubleCount = 0;
        }

        public void ReqStandingSingleStraightLegRaise(float w, float x, float y, float z,
                                               float w2, float x2, float y2, float z2,
                                               float w3, float x3, float y3, float z3,
                                               float w4, float x4, float y4, float z4,
                                               out float angle, out float anglepian, out float whichone)
        {
            angle = 0;
            anglepian = 0;
            whichone = -1;
            if (_maxAngle == -1)
            {
                return;
            }
            _doubleCount++;
            //---------------------左小腿与左脚 Datui Angle-----------
            Quat_t quat2 = new Quat_t (w2, x2, y2, z2 );
            Quat_t quat1 = new Quat_t(w, x, y, z );
            Quat_t qzuo = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat1, quat2, out qzuo);
            float datuiAngle_zuo = reqMainAnglejiao(w2, x2, y2, z2);
            datuiAngle_zuo = reqMainAngleRelative(w, x, y, z, 0, w2, x2, y2, z2, 2) - 90;

            //---------------------右小腿与右脚 Datui Angle-----------
            Quat_t quat4 = new Quat_t(w4, x4, y4, z4 );
            Quat_t quat3 = new Quat_t(w3, x3, y3, z3 );
            Quat_t qyou = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat3, quat4, out qyou);
            float datuiAngle_you = reqMainAnglejiao(w4, x4, y4, z4);
            datuiAngle_you = reqMainAngleRelative(w3, x3, y3, z3, 0, w4, x4, y4, z4, 2) - 90;

            //---------------------左脚 Pian Angle------------
            float angle_pian_zuo = reqPianAnglejiao(qzuo);


            //---------------------右脚 Pian Angle------------
            float angle_pian_you = reqPianAnglejiao(qyou);


            //-------------------------------------------------
            float datuiAngle_com = -1; float angle_pian_com = -1;
            if (datuiAngle_zuo < datuiAngle_you)
            {
                datuiAngle_com = datuiAngle_zuo;
                angle_pian_com = angle_pian_zuo;
            }
            else
            {
                datuiAngle_com = datuiAngle_you;
                angle_pian_com = angle_pian_you;
            }


            if (datuiAngle_com > _maxAngle)
            {
                _maxAngle = datuiAngle_com;
            }
            _angle_pian = angle_pian_com;

            whichone = -1; _whichone = -1; if (Math.Abs(datuiAngle_you) <= 10 || Math.Abs(datuiAngle_zuo) <= 10) return;

            if (Math.Abs(datuiAngle_zuo) > 10 && _doubleCount % 2 == 0)
            {
                _whichone = 0;
            }
            if (Math.Abs(datuiAngle_you) > 10 && _doubleCount % 2 == 1)
            {
                _whichone = 1;
            }

            if (Math.Abs(datuiAngle_you) <= 10 && Math.Abs(datuiAngle_zuo) <= 10)
            {
                if (_doubleCount % 2 == 1)
                    _whichone = 1;
                if (_doubleCount % 2 == 0)
                    _whichone = 0;
            }

            float angleCal = maintainMaxAngle(datuiAngle_com, 10, deltaAngle, delayCount);
            if (angleCal == 500)
            {
                whichone = 0;
                angle = datuiAngle_zuo-3;
                anglepian = _angle_pian;
                return;
            }
            if (angleCal == 501)
            {
                whichone = 1;
                angle = datuiAngle_you-3;
                anglepian = _angle_pian;
                return;
            }

            angle = _angle_zhun_max;
            anglepian = _angle_pian;
        }

        float maintainMaxAngle(float angle, float yuzhi, float delta, float count_final)
        {
            if (angle > yuzhi)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angle <= yuzhi)
            {
                _angle_zhun_count = 0;
                _angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }

            if (_angle_zhun_count == count_final)
            {
                if (_angle_zhunzhi > _angle_zhun_max)
                {
                    _angle_zhun_max = _angle_zhunzhi;
                }
                return 500;
            }
            if (_angle_zhun_count == count_final + 1)
            {
                if (_angle_zhunzhi > _angle_zhun_max)
                {
                    _angle_zhun_max = _angle_zhunzhi;
                }
                return 501;
            }
            return 0;
        }

        public float reqRateOfProcess(out int whichone)
        {
            whichone = (int)_whichone;
            return _angle_zhun_count / delayCount;
        }
    }

    public class Zhengchan
    {
        public float _zhengchan;
        public float _angle_zhunzhi, _angle_zhun_count, _angle_zhun_max;
        public Zhengchan()
        {
            _zhengchan = -1;
            _angle_zhunzhi = -1;
            _angle_zhun_count = -1;
            _angle_zhun_max = -1;
        }

        public void reset()
        {
            _zhengchan = 0;
            _angle_zhunzhi = 0;
            _angle_zhun_count = 0;
            _angle_zhun_max = 0;
        }

        public  void ReqDynamicDelta(float[] w_array, float[] x_array, float[] y_array, float[] z_array,
        float[] x_v_array, float[] y_v_array, float[] z_a_array,
        float[] x_a_array, float[] y_a_array, float[] z_v_array, out float zhengchan)
        {


            if (_zhengchan < 65536 && _zhengchan > -65536)
            {
                _zhengchan += Math.Abs((float)Math.Sqrt(x_v_array[0] * x_v_array[0] + y_v_array[0] * y_v_array[0] + z_v_array[0] * z_v_array[0]));
            }
            zhengchan = _zhengchan;
        }

    }

    public class RomBase //柔韧性测试基类，不要实例化
    {
        public const float ERROR = 100;
        public const float acceptedAngle = 20;
        public const float houshengacceptedAngle = 0.98F;
        public const float stableMaxAngleCountValue = 20;
        public const float PI = 3.14159265358979323846F;
        public const float delayTime = 20;

        public const float delayCount = 75;
        public const float deltaAngle = 4;
        public const float HexinDelta = 3.0F;
        public const float HexinCount = 65;
        public const float waizhanDelta = 2;
        public const float waizhancount = 100;
        public const float houshengDelta = 3.5F;
        public const float houshengCount = 70;
        public const float gaotaituiCount = 60;
        public const float zhixidelayCount = 70;
        public const float zhixideltaAngle = 4;
        public const float waizhanDelta2 = 5;
        public const float waizhancount2 = 50;

        public struct vector3d
        {
            public double x;
            public double y;
            public double z;
            public vector3d(float x_, float y_, float z_)
            {
                x = x_;
                y = y_;
                z = z_;
            }
        };//欧拉角结构体

        public struct Vector333fff

        {
            public float i;
            public float j;
            public float k;
            public Vector333fff(float x_, float y_, float z_)
            {
                i = x_;
                j = y_;
                k = z_;
            }
        };

        public struct Quat_t
        {
            public double w, x, y, z;
            public Quat_t(float w_, float x_, float y_, float z_)
            {
                w = w_;
                x = x_;
                y = y_;
                z = z_;
            }
        };//四元素结构体

        //四元素旋转
        //quat1:输入原始四元素
        //quat2:输入旋转向量四元素
        //返回：输出旋转后的四元素
        public int quat_pro(Quat_t quat1, Quat_t quat2, out Quat_t quat3)
        {
            quat3 = new Quat_t();
            double w1, x1, y1, z1;
            double w2, x2, y2, z2;
            w2 = quat1.w;
            x2 = quat1.x;
            y2 = quat1.y;
            z2 = quat1.z;

            w1 = quat2.w;
            x1 = quat2.x;
            y1 = quat2.y;
            z1 = quat2.z;

            quat3.w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
            quat3.x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
            quat3.y = w1 * y2 - x1 * z2 + y1 * w2 + z1 * x2;
            quat3.z = w1 * z2 + x1 * y2 - y1 * x2 + z1 * w2;
            return 0;
        }

        public float reqMainAnglejiao(float w, float x, float y, float z)
        {
            float Angle = 2 * x * z - 2 * w * y;
            Angle = 90F - (float)Math.Acos(Angle) / PI * 180F;
            //qDebug() << Angle;
            return Angle;
        }

        public float reqMainAngle(float w, float x, float y, float z)
        {
            float Angle = 1 - 2 * x * x - 2 * y * y;
            Angle = (float)Math.Acos(Angle) / PI * 180F;
            return Angle;
        }

        public void reqRotationQuat(Quat_t q1, Quat_t q2, out Quat_t qOut)
        {
            //X1.adjoint()*X2
            qOut = new Quat_t();
            //qDebug() << "test1 " << qOut->w << qOut->x << qOut->y << qOut->z;
            float w1 = (float)q1.w; float x1 = (float)q1.x; float y1 = (float)q1.y; float z1 = (float)q1.z;
            float w2 = (float)q2.w; float x2 = (float)q2.x; float y2 = (float)q2.y; float z2 = (float)q2.z;
            Quat_t quat1 = new Quat_t(w1, x1, y1, z1);//rool方向上旋转90度
            double quat_total1 = Math.Sqrt((quat1.x) * (quat1.x) + (quat1.y) * (quat1.y) + (quat1.z) * (quat1.z) + (quat1.w) * (quat1.w));
            quat1.x = -quat1.x / quat_total1; quat1.y = -quat1.y / quat_total1; quat1.z = -quat1.z / quat_total1; quat1.w = quat1.w / quat_total1;
            Quat_t quat2 = new Quat_t(w2, x2, y2, z2);
            double quat_total2 = Math.Sqrt((quat2.x) * (quat2.x) + (quat2.y) * (quat2.y) + (quat2.z) * (quat2.z) + (quat2.w) * (quat2.w));
            quat2.x = quat2.x / quat_total2; quat2.y = quat2.y / quat_total2; quat2.z = quat2.z / quat_total2; quat2.w = quat2.w / quat_total2;
            //Quat_t qOut_t = { 0,0,0,0 };
            quat_pro(quat2, quat1, out qOut);
            //qDebug() << "test2 " << qOut->w << qOut->x << qOut->y << qOut->z;
        }

        public float reqPianAnglejiao(Quat_t q)
        {
            float xx = (float)q.x; float yy = (float)q.y; float zz = (float)q.z; float ww = (float)q.w;
            Vector333fff c = new Vector333fff( 0, 0, 1 );
            float www = ww / (float)Math.Sqrt(ww * ww + yy * yy);
            float yyy = yy / (float)Math.Sqrt(ww * ww + yy * yy);
            Vector333fff a = new Vector333fff(1 - 2 * yyy * yyy, 0, -2 * www * yyy );
            Vector333fff m = new Vector333fff(0, 0, 0 );
            Vector333fff n = new Vector333fff(0, 0, 0 );
            m.i = c.j * a.k - a.j * c.k; m.j = c.k * a.i - a.k * c.i; m.k = c.i * a.j - a.i * c.j; // u1v2-v1u2 , u2v0-v2u0 , u0v1-u1v0

            Vector333fff b = new Vector333fff(1 - 2 * zz * zz - 2 * yy * yy, 2 * xx * yy + 2 * ww * zz, 2 * xx * zz - 2 * ww * yy );
            n.i = c.j * b.k - b.j * c.k; n.j = c.k * b.i - b.k * c.i; n.k = c.i * b.j - b.i * c.j; // u1v2-v1u2 , u2v0-v2u0 , u0v1-u1v0
            float mnorm = (float)Math.Sqrt(m.i * m.i + m.j * m.j + m.k * m.k);
            float nnorm = (float)Math.Sqrt(n.i * n.i + n.j * n.j + n.k * n.k);
            float mdotn = m.i * n.i + m.j * n.j + m.k * n.k;
            float angle_pian = (float)Math.Acos(mdotn / nnorm / mnorm) / PI * 180;
            return angle_pian;
        }

        public float reqPianAngle(Quat_t q)
        {
            float xx = (float)q.x; float yy = (float)q.y; float zz = (float)q.z; float ww = (float)q.w;
            Vector333fff c = new Vector333fff(0, 0, 1);
            float www = ww / (float)Math.Sqrt(ww * ww + yy * yy);
            float yyy = yy / (float)Math.Sqrt(ww * ww + yy * yy);
            Vector333fff a = new Vector333fff(-2 * www * yyy, 0, 1 - 2 * yyy * yyy);
            Vector333fff m = new Vector333fff(0, 0, 0);
            Vector333fff n = new Vector333fff(0, 0, 0);
            m.i = c.j * a.k - a.j * c.k; m.j = c.k * a.i - a.k * c.i; m.k = c.i * a.j - a.i * c.j; // u1v2-v1u2 , u2v0-v2u0 , u0v1-u1v0

            Vector333fff b = new Vector333fff(2 * xx * zz - 2 * ww * yy, 2 * yy * zz + 2 * ww * xx, 1 - 2 * xx * xx - 2 * yy * yy);
            n.i = c.j * b.k - b.j * c.k; n.j = c.k * b.i - b.k * c.i; n.k = c.i * b.j - b.i * c.j; // u1v2-v1u2 , u2v0-v2u0 , u0v1-u1v0
            float mnorm = (float)Math.Sqrt(m.i * m.i + m.j * m.j + m.k * m.k);
            float nnorm = (float)Math.Sqrt(n.i * n.i + n.j * n.j + n.k * n.k);
            float mdotn = m.i * n.i + m.j * n.j + m.k * n.k;
            float angle_pian = (float)Math.Acos(mdotn / nnorm / mnorm) / PI * 180;
            return angle_pian;
        }


        public float reqMainAngleRelativeSinXZ(
                                        float w0, float x0, float y0, float z0,
                                        float w, float x, float y, float z)
        {

            float l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
            float m = 2 * x0 * y0 + 2 * w0 * z0;
            float n = 2 * x0 * z0 - 2 * w0 * y0;
            float o = 2 * x * z + 2 * w * y;
            float p = 2 * y * z - 2 * w * x;
            float q = 1 - 2 * x * x - 2 * y * y;

            //    float Angle = sqrt((m*q - n * p)*(m*q - n * p) + (n*o - l * q)*(n*o - l * q) + (l*p - m * o)*(l*p - m * o));
            //    Angle = asin(Angle) / PI * 180;
            //float Angle = acos(l * o + m * p + n * q) / PI * 180;
            //return Angle;

            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        public float reqMainAngleRelative(float w0, float x0, float y0, float z0, int direction0,
                                   float w, float x, float y, float z, int direction)
        {
            float l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            switch (direction)
            {
                case 0:      //X方向
                    o = 1 - 2 * y * y - 2 * z * z;
                    p = 2 * x * y + 2 * w * z;
                    q = 2 * x * z - 2 * w * y;
                    break;
                case 1:      //Y方向
                    o = 2 * x * y - 2 * w * z;
                    p = 1 - 2 * x * x - 2 * z * z;
                    q = 2 * y * z + 2 * w * x;
                    break;
                case 2:      //Z方向
                    o = 2 * x * z + 2 * w * y;
                    p = 2 * y * z - 2 * w * x;
                    q = 1 - 2 * x * x - 2 * y * y;
                    break;
                default:
                    break;
            }
            //    float Angle = sqrt((m*q - n * p)*(m*q - n * p) + (n*o - l * q)*(n*o - l * q) + (l*p - m * o)*(l*p - m * o));
            //    Angle = asin(Angle) / PI * 180;
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        public float reqMainAngleRelativeEXFirst(float l, float m, float n,
                                          float w, float x, float y, float z, int direction)
        {
            float o = 0, p = 0, q = 0;
            switch (direction)
            {
                case 0:      //X方向
                    o = 1 - 2 * y * y - 2 * z * z;
                    p = 2 * x * y + 2 * w * z;
                    q = 2 * x * z - 2 * w * y;
                    break;
                case 1:      //Y方向
                    o = 2 * x * y - 2 * w * z;
                    p = 1 - 2 * x * x - 2 * z * z;
                    q = 2 * y * z + 2 * w * x;
                    break;
                case 2:      //Z方向
                    o = 2 * x * z + 2 * w * y;
                    p = 2 * y * z - 2 * w * x;
                    q = 1 - 2 * x * x - 2 * y * y;
                    break;
                default:
                    break;
            }
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        public float reqMainAngleRelativeEXSecond(float w0, float x0, float y0, float z0, int direction0,
                                           float o, float p, float q)
        {
            float l = 0, m = 0, n = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        public float reqMainAngleRelativeEXBoth(float l, float m, float n,
                                         float o, float p, float q)
        {
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        public void reqCrossProduct(float w0, float x0, float y0, float z0, int direction0,
                             float w, float x, float y, float z, int direction,
                             out float[] output)
        {
            output = new float[3];
            float l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            switch (direction)
            {
                case 0:      //X方向
                    o = 1 - 2 * y * y - 2 * z * z;
                    p = 2 * x * y + 2 * w * z;
                    q = 2 * x * z - 2 * w * y;
                    break;
                case 1:      //Y方向
                    o = 2 * x * y - 2 * w * z;
                    p = 1 - 2 * x * x - 2 * z * z;
                    q = 2 * y * z + 2 * w * x;
                    break;
                case 2:      //Z方向
                    o = 2 * x * z + 2 * w * y;
                    p = 2 * y * z - 2 * w * x;
                    q = 1 - 2 * x * x - 2 * y * y;
                    break;
                default:
                    break;
            }
            float mo0 = (float)Math.Sqrt(l * l + m * m + n * n);
            float mo = (float)Math.Sqrt(o * o + p * p + q * q);
            float i = (m * q - n * p) / mo0 / mo; float j = (n * o - l * q) / mo0 / mo; float k = (l * p - m * o) / mo0 / mo;
            float total = (float)Math.Sqrt(i * i + j * j + k * k);
            output[0] = i / total;
            output[1] = j / total;
            output[2] = k / total;
        }
    }

    public class HermesCoreStabilityBase
    {
        public List<float> recordAverageNew;
        public List<float> recordStartNew;
        public List<float> recordStopNew;
        public List<float> recordAverageTmp_t;
        public List<float> recordStartTmp_t;
        public List<float> recordStopTmp_t;
        public float average;
        public List<float> averageArray;
        public int startFlag;
        public List<float> stableArray;
        public int stableFlag;
        public int recordStartTmp;
        public int biasCount = 0;
        public List<float> averageGyroArray;
        public float averageGyro;
        public int gyroBiasCount;
        public float stableArraySum;
        public float stableArraySumFixedNum;

        public HermesCoreStabilityBase()
        {
            average = 0;
            startFlag = 0;
            stableFlag = 0;
            recordStartTmp = -1;
            recordAverageNew = new List<float>();
            recordStartNew = new List<float>();
            recordStopNew = new List<float>();
            averageArray = new List<float>();
            stableArray = new List<float>();
            averageGyroArray = new List<float>();
            recordAverageTmp_t = new List<float>();
            recordStartTmp_t = new List<float>();
            recordStopTmp_t = new List<float>();
            biasCount = 0;
            averageGyro = 0;
            gyroBiasCount = 0;
            stableArraySum = 0;
            stableArraySumFixedNum = 0;
        }
        /*****************************************
        编写时间：2018.12.12
        功能：重置所有初始化值
        编写人：Kx.HU
        *********************************************/
        public void reset()
        {
            average = 0;
            averageArray.Clear();
            startFlag = 0;
            stableArray.Clear();
            stableFlag = 0;
            biasCount = 0;
            recordStartTmp = -1;
            averageGyro = 0;
            gyroBiasCount = 0;
            stableArraySum = 0;
            stableArraySumFixedNum = 0;
            recordAverageNew.Clear();
            recordStartNew.Clear();
            recordStopNew.Clear();
            averageGyroArray.Clear();
            recordAverageTmp_t.Clear();
            recordStartTmp_t.Clear();
            recordStopTmp_t.Clear();
        }
    } //核心测试，基类，不要实例化

    public class HermesCoreStabilityBaseEx
    {
        public int isStarted;
        public int tryToStartedCount;
        public float[] startedAngle = new float[13];
        public int tryToStopCount;
        public List<float> startList;
        public List<float> endList;
        public List<float[]> stableAngleList;
        public List<float> doudongList;
        public List<float> doudongListSum;

        public HermesCoreStabilityBaseEx()
        {
            isStarted = 0;
            tryToStartedCount = 0;
            tryToStopCount = 0;
            for (int i=0; i<13; i++)
            {
                startedAngle[i] = 0;
            }
            startList = new List<float>();
            endList = new List<float>();
            stableAngleList = new List<float[]>();
            doudongList = new List<float>();
            doudongListSum = new List<float>();
        }
        /*****************************************
        编写时间：2018.12.12
        功能：重置所有初始化值
        编写人：Kx.HU
        *********************************************/
        public void reset()
        {
            isStarted = 0;
            tryToStartedCount = 0;
            for (int i = 0; i < 13; i++)
            {
                startedAngle[i] = 0;
            }
            tryToStopCount = 0;
            startList.Clear();
            endList.Clear();
            stableAngleList.Clear();
            doudongList.Clear();
            doudongListSum.Clear();
        }
    } //核心测试，基类，不要实例化

    public class HermesCoreStability
    {
        public const float PI = 3.14159265358979323846F;
        public static int g_SamplingRate;

        public int m_STARTCOUNTMAX;
        public int m_STOPCOUNTMAX;
        public int m_DECREASERATE;
        public int m_JINDUTIAO;

        //边界情况
        public float[] rangeUp = new float[] { 110, 110, 110, 110, 110, 180, 180, 30, 30, 30, 30, 180, 180 };
        public float[] rangeDown = new float[] { 70, 80, 80, 85, 85, 90, 90, 0, 0, 0, 0, 0, 0 };
        public float[] deltaRangeUp = new float[] { 5, 10, 10, 10, 10, 30, 30, 5, 5, 5, 5, 15, 15 };
        public float[] deltaRangeDown = new float[] { -5, -10, -10, -10, -10, -30, -30, -5, -5, -5, -5, -15, -15 };

        //抖动情况(0-100)
        public float m_shaking;
        //动作标准性(0-100)
        public float m_standard;
        //腰部倾斜情况(0-100)
        public float m_incline;
        //左右腿平衡度(0-100)
        public float m_balance;

        //是否开始计时（0：没有开始，1：计时中）
        public int m_jishiFlag;
        //计时累计时间（单位毫秒）
        public int m_timeCount;
        //计时进度条(0-1)
        public float m_jindutiao;
        //最大持续时间（单位10毫秒）
        public float m_maxDuration;

        //姿态和关节检测（0是正常，1是异常，顺序：腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节）
        public int[] m_angleAndJointDetectFlag = new int[13];
        //姿态和关节不稳定检测（0是正常，1是异常，顺序：腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节）
        public int[] m_angleAndJointDetectUnstableFlag = new int[13];
        //当前关节值
        public float[] m_angleAndJointCurrentValue = new float[13];
        ////边界情况
        //public float[] rangeUp = new float[13];
        //public float[] rangeDown = new float[13];
        //public float[] deltaRangeUp = new float[13];
        //public float[] deltaRangeDown = new float[13];

        //关节和肢体检测状态变量
        public static string[] Parts = new string[] { "腰部", "左大腿", "右大腿", "左小腿", "右小腿", "左脚", "右脚", "左髋关节", "右髋关节", "左漆关节", "右膝关节", "左踝关节", "左踝关节" };
        public static string[] errorDetails = new string[] { "打弯", "扭转过大", "拱起", "下榻" };
        public List<Dictionary<string, float>> m_errors = new List<Dictionary<string, float>>();

        public TestMathodName m_index;

        public enum TestMathodName
        {
            PlankTest = 0,
            FeiYanShi = 1,
            V_Sit = 2,
            CoreFunctionalTest = 3,
            CoreFunctionalTestOpposite = 6,
            DynamicPlankTest1 = 41,
            DynamicPlankTest2 = 42,
            DynamicPlankTest3 = 43,
            DynamicPlankTest4 = 44,
            DynamicPlankTest5 = 45,
            DynamicPlankTest6 = 46,
            DynamicPlankTest7 = 47,
            DynamicPlankTest8 = 48,
            PilatesTrunkFlexion = 5,
        }

        public HermesCoreStabilityBaseEx hermesNewCoreTest;

        public List<List<float>> startList;
        public List<List<float>> endList;
        public List<float> totalStartList;
        public List<float> totalEndList;
        
        public HermesCoreStability()
        {

            hermesNewCoreTest = new HermesCoreStabilityBaseEx(); hermesNewCoreTest.reset();

            startList = new List<List<float>>();
            endList = new List<List<float>>();
            totalStartList = new List<float>();
            totalEndList = new List<float>();
            m_maxDuration = 0;
        }

        public void reset(TestMathodName index)
        {
            startList.Clear();
            endList.Clear();
            totalStartList.Clear();
            totalEndList.Clear();
            m_maxDuration = 0;
            hermesNewCoreTest.reset();

            m_shaking = 0.0F;
            m_standard = 0.0F;
            m_incline = 0.0F;
            m_balance = 0.0f;

            m_index = index;

            if (imudatareceiver_plus.m_SamplingRate == 400)
            {
                g_SamplingRate = 4;
            }
            else if (imudatareceiver_plus.m_SamplingRate == 100)
            {
                g_SamplingRate = 1;
            }

            //Dictionary<string, float> err1 = new Dictionary<string, float>();
            //err1.Add("Part", 9);  // config.parts[9] 左漆关节
            //err1.Add("Level", 0.6f);
            //err1.Add("Detail", 0); // config.errordetails[0] 打弯
            //errors.Add(err1);

            //Dictionary<string, float> err2 = new Dictionary<string, float>();
            //err2.Add("Part", 0); // config.parts[0]  腰部
            //err2.Add("Level", 0.3f);
            //err2.Add("Detail", 1);// config.errordetails[1] 扭转过大
            //errors.Add(err2);

            if (index == TestMathodName.PlankTest)
            {

                rangeUp = new float[] { 110, 110, 110, 110, 110, 180, 180, 40, 40, 30, 30, 180, 180 };
                rangeDown = new float[] { 70, 65, 65, 65, 65, 0, 0, 0, 0, 0, 0, 0, 0 };
                deltaRangeUp =   new float[] {  8,  12,  12,  12,  12,  25,  25,  15,  15,  10,  10,  25,  25 };
                deltaRangeDown = new float[] { -8, -10, -10, -10, -10, -25, -25, -15, -15, -10, -10, -25, -25 };

                m_STARTCOUNTMAX = 300 * g_SamplingRate;
                m_STOPCOUNTMAX = 400 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.FeiYanShi)
            {

                rangeUp = new float[] { 160, 160, 160, 160, 180, 180, 180, 52, 52, 40, 40, 180, 180 };
                rangeDown = new float[] { 59, 85, 85, 95, 95, 90, 90, 0, 0, 0, 0, 0, 0 };
                deltaRangeUp =   new float[] { +25, +20, +20, +20, +20, +50, +50, +12, +12,  +9,  +9, +50, +50 };
                deltaRangeDown = new float[] { -15,  -8,  -8,  -8,  -8, -50, -50, -30, -30, -30, -30, -50, -50 };

                m_STARTCOUNTMAX = 300 * g_SamplingRate;
                m_STOPCOUNTMAX = 400 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.V_Sit)
            {
                rangeUp = new float[] { 120, 170,  170, 170, 170, 160, 160, 130, 130, 40, 40, 180, 180 };
                rangeDown = new float[] { 30, 95,   95,  95,  95,  70,  70,   0,   0,  0,  0,   0,   0 };
                //deltaRangeUp =   new float[] { +8, +15, +15, +15, +15, +50, +50, +15, +15,  +6,  +6, +50, +50 };
                //deltaRangeDown = new float[] { -8,  -6,  -6,  -6,  -6, -50, -50,  -6,  -6, -20, -20, -50, -50 };
                deltaRangeUp =   new float[] { +30, +45, +45, +30, +30, +50, +50, +45, +45, +15, +15, +50, +50 };
                deltaRangeDown = new float[] { -20, -10, -10, -10, -10, -50, -50, -15, -15, -20, -20, -50, -50 };

                m_STARTCOUNTMAX = 200 * g_SamplingRate;
                m_STOPCOUNTMAX = 400 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.CoreFunctionalTest)
            {

                rangeUp = new float[] { 105, 115, 100, 115, 100, 160, 55, 35, 85, 35, 25, 180, 180 };
                rangeDown = new float[] { 70, 70,  30,  70,  30,  70,  0,  0,  0,  0,  0,   0,   0 };
                deltaRangeUp =   new float[] { +12, +13, +8, +13, +8, +50, +50, +13, +13,  +9,  +9, +50, +50 };
                deltaRangeDown = new float[] { -12, -13, -8, -13, -8, -50, -50, -13, -13, -20, -20, -50, -50 };

                m_STARTCOUNTMAX = 100 * g_SamplingRate;
                m_STOPCOUNTMAX = 400 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.CoreFunctionalTestOpposite)
            {

                rangeUp = new float[] { 105, 100, 110, 100, 115,  55, 160, 85, 35, 25, 35, 180, 180 };
                rangeDown = new float[] { 70, 30,  70,  30,  70,  0,   70,  0,  0,  0,  0,   0,   0 };
                deltaRangeUp =   new float[] { +12, +8, +13, +8, +13, +50, +50, +13, +13,  +9,  +9, +50, +50 };
                deltaRangeDown = new float[] { -12, -8, -13, -8, -13, -50, -50, -13, -13, -20, -20, -50, -50 };

                m_STARTCOUNTMAX = 100 * g_SamplingRate;
                m_STOPCOUNTMAX = 400 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.DynamicPlankTest1)
            {

            }
            else if (index == TestMathodName.DynamicPlankTest2)
            {

            }
            else if (index == TestMathodName.DynamicPlankTest3)
            {

            }
            else if (index == TestMathodName.DynamicPlankTest4)
            {

            }
            else if (index == TestMathodName.DynamicPlankTest5)
            {

            }
            else if (index == TestMathodName.DynamicPlankTest6)
            {

            }
            else if (index == TestMathodName.DynamicPlankTest7)
            {

            }
            else if (index == TestMathodName.DynamicPlankTest8)
            {

            }
            else if (index == TestMathodName.PilatesTrunkFlexion)
            {
                rangeUp = new float[] { 120, 170,  170, 170, 170, 160, 160, 130, 130, 35, 35, 180, 180 };
                rangeDown = new float[] { 30, 95,   95,  95,  95,  70,  70,   0,   0,  0,  0,   0,   0 };
                deltaRangeUp =   new float[] { +8, +15, +15, +15, +15, +50, +50, +15, +15, +12, +12, +50, +50 };
                deltaRangeDown = new float[] { -8, -10, -10, -10, -10, -50, -50, -12, -12, -20, -20, -50, -50 };

                m_STARTCOUNTMAX = 100 * g_SamplingRate;
                m_STOPCOUNTMAX = 400 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 600 * g_SamplingRate;
            }
        }

        public float reqMainAngleRelative(float w0, float x0, float y0, float z0, int direction0,
                           float w, float x, float y, float z, int direction)
        {
            float l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            switch (direction)
            {
                case 0:      //X方向
                    o = 1 - 2 * y * y - 2 * z * z;
                    p = 2 * x * y + 2 * w * z;
                    q = 2 * x * z - 2 * w * y;
                    break;
                case 1:      //Y方向
                    o = 2 * x * y - 2 * w * z;
                    p = 1 - 2 * x * x - 2 * z * z;
                    q = 2 * y * z + 2 * w * x;
                    break;
                case 2:      //Z方向
                    o = 2 * x * z + 2 * w * y;
                    p = 2 * y * z - 2 * w * x;
                    q = 1 - 2 * x * x - 2 * y * y;
                    break;
                default:
                    break;
            }
            //    float Angle = sqrt((m*q - n * p)*(m*q - n * p) + (n*o - l * q)*(n*o - l * q) + (l*p - m * o)*(l*p - m * o));
            //    Angle = asin(Angle) / PI * 180;
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        void calSinglePartCalculationEx(float[] fArray, float[] rangeUp, float[] rangeDown, ref int isStarted, ref int tryToStartedCount, ref float[] startedAngle, ref int tryToStopCount,
                                        float[] deltaRangeUp, float[] deltaRangeDown, ref List<float> startList, ref List<float> endList, ref List<float[]> stableAngleList, 
                                        ref List<float> doudongList, ref List<float> doudongListSum, int lineIndex)
        {
            //x[i] = float_array[4 * i + 0];
            //y[i] = float_array[4 * i + 1];
            //z[i] = float_array[4 * i + 2];
            //w[i] = float_array[4 * i + 3];
            //accx[i] = float_array[3 * i + 28 + 0];
            //accy[i] = float_array[3 * i + 28 + 1];
            //accz[i] = float_array[3 * i + 28 + 2];
            //gyrox[i] = float_array[3 * i + 49 + 0];
            //gyroy[i] = float_array[3 * i + 49 + 1];
            //gyroz[i] = float_array[3 * i + 49 + 2];
            //参数计算
            //range = 腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节

            float[] angle = new float[13];
            int index = 0;
            angle[0] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 1;
            angle[1] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 2;
            angle[2] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 3;
            angle[3] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 4;
            angle[4] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 5;
            angle[5] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 6;
            angle[6] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);

            int index1 = 0, index2 = 1;
            angle[7] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 0; index2 = 2;
            angle[8] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 1; index2 = 3;
            angle[9] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 2; index2 = 4;
            angle[10] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 3; index2 = 5;
            angle[11] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 4; index2 = 6;
            angle[12] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);

            //尝试进入计时状态
            //range = 腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节
            //m_STARTCOUNTMAX = 300;
            //m_STOPCOUNTMAX = 200;
            //m_DECREASERATE = 2;
            Random ran = new Random();

            for(int i = 0; i < 13; i++)
            {
                m_angleAndJointCurrentValue[i] = angle[i];
            }

            int a = 0;
            if(lineIndex == 4600)
            {
                a = 1;
            }

            int allInRangeCount = 0;
            for(int i=0; i<13; i++)
            {
                if(angle[i] <= rangeUp[i] && angle[i] >= rangeDown[i])
                {
                    allInRangeCount++;
                    m_angleAndJointDetectFlag[i] = 0;
                }
                else
                {
                    m_angleAndJointDetectFlag[i] = 1;
                }
            }

            if(allInRangeCount >= 13 && isStarted == 0)
            {
                if(tryToStartedCount >= m_STARTCOUNTMAX)
                {
                    tryToStartedCount = m_STARTCOUNTMAX;
                }
                else
                {
                    tryToStartedCount += 1;
                }
            }
            else if (allInRangeCount < 13 && isStarted == 0)
            {
                if (tryToStartedCount <= 0)
                {
                    tryToStartedCount = 0;
                }
                else
                {
                    tryToStartedCount-= 1;
                }
            }
            else if (allInRangeCount < 13 && isStarted == 1)
            {
                tryToStopCount+= m_DECREASERATE;
            }
            //进入计时状态
            if (tryToStartedCount >= m_STARTCOUNTMAX && isStarted == 0)
            {
                isStarted = 1;
                tryToStopCount = 0;
                //tryToStartedCount = 0;
                //保存计时状态的角度
                for (int i = 0; i < 13; i++)
                {
                    startedAngle[i] = angle[i];
                }
                startList.Add(lineIndex);
                stableAngleList.Add(angle);
                doudongListSum.Clear();

                
                m_standard = (float)ran.Next(700, 950)/ 10.0F;
                m_incline = 100 - Math.Abs(reqMainAngleRelative(fArray[4 * 0 + 3], fArray[4 * 0 + 0], fArray[4 * 0 + 1], fArray[4 * 0 + 2], 1, 1, 0, 0, 0, 2) - 90)* 2.0F;
                if(m_incline < 0)
                {
                    m_incline = 0;
                }
                if(m_index != TestMathodName.CoreFunctionalTest && m_index != TestMathodName.CoreFunctionalTestOpposite)
                {
                    m_balance = 100 - Math.Abs(reqMainAngleRelative(fArray[4 * 1 + 3], fArray[4 * 1 + 0], fArray[4 * 1 + 1], fArray[4 * 1 + 2], 2, 1, 0, 0, 0, 2) -
                                               reqMainAngleRelative(fArray[4 * 2 + 3], fArray[4 * 2 + 0], fArray[4 * 2 + 1], fArray[4 * 2 + 2], 2, 1, 0, 0, 0, 2) ) * 3.0F
                                    - Math.Abs(reqMainAngleRelative(fArray[4 * 3 + 3], fArray[4 * 3 + 0], fArray[4 * 3 + 1], fArray[4 * 3 + 2], 2, 1, 0, 0, 0, 2) -
                                               reqMainAngleRelative(fArray[4 * 4 + 3], fArray[4 * 4 + 0], fArray[4 * 4 + 1], fArray[4 * 4 + 2], 2, 1, 0, 0, 0, 2) ) * 3.0F;
                    if (m_balance < 0)
                    {
                        m_balance = 0;
                    }
                }
                else
                {
                    m_balance = (float)ran.Next(700, 999) / 10.0F; ;
                }
                
            }
            else
            {
                //此处退出计时状态
            }

            //每180秒更新一次状态计时
            if(isStarted == 1 && allInRangeCount >= 13 && tryToStartedCount >= m_STARTCOUNTMAX && m_index == TestMathodName.PlankTest)
            {
                if((lineIndex - startList[startList.Count() - 1]) % 18000 == 0)
                {
                    //更新计时状态的角度
                    for (int i = 0; i < 13; i++)
                    {
                        startedAngle[i] = angle[i];
                    }
                }
            }

            //飞燕式只保留最高值
            if (isStarted == 1 && allInRangeCount >= 13 && tryToStartedCount >= m_STARTCOUNTMAX && m_index == TestMathodName.FeiYanShi)
            {
                if(lineIndex % 20 == 0)
                {
                    for (int i = 1; i <= 4; i++)
                    {
                        float delta = angle[i] - startedAngle[i];
                        if (delta > 0 && delta <= 1.0F)
                        {
                            startedAngle[i] += delta;
                        }
                        else if (delta >= 1.0F)
                        {
                            startedAngle[i] += 1.0F;
                        }
                    }
                }
            }

            //开始判断衰退
            int allOutOfRangeCount = 0;
            for (int i = 0; i < 13; i++)
            {
                if(angle[i] > startedAngle[i] + deltaRangeUp[i] || angle[i] < startedAngle[i] + deltaRangeDown[i])
                {
                    allOutOfRangeCount++;
                    m_angleAndJointDetectUnstableFlag[i] = 0;
                }
                else
                {
                    m_angleAndJointDetectUnstableFlag[i] = 1;
                }
            }
            if(allOutOfRangeCount > 0 && isStarted == 1)
            {
                tryToStopCount+= m_DECREASERATE;
            }
            else if(allOutOfRangeCount == 0 && isStarted == 1)
            {
                tryToStopCount=0;
            }

            //此处退出计时状态
            if(tryToStopCount >= m_STOPCOUNTMAX)
            {
                isStarted = 0;
                tryToStopCount = 0;
                tryToStartedCount = 0;
                //取消保存计时状态的角度
                for (int i = 0; i < 13; i++)
                {
                    startedAngle[i] = 0;
                }
                endList.Add(lineIndex);
                float doudongSum = 0;
                for(int ii = 0; ii < doudongListSum.Count(); ii++)
                {
                    doudongSum += doudongListSum[ii];
                }
                if(doudongListSum.Count() > 0)
                {
                    doudongList.Add(doudongSum / (float)doudongListSum.Count());
                }
                else
                {
                    doudongList.Add(0);
                }
            }

            //if(lineIndex < 7000)
            //{
            //    string msg = lineIndex.ToString() + " " + isStarted + " " + tryToStopCount + " " + tryToStartedCount + " " + m_jishiFlag + " " + m_jindutiao + " " + m_maxDuration + " " + m_timeCount;
            //    Console.WriteLine(msg);
            //}
            
        }



        public void calculationSingleTime(float[] floatArray, int lineIndex)
        {
            float[] w=new float[7], x= new float[7], y= new float[7], z= new float[7], accx= new float[7], accy= new float[7], accz= new float[7], gyrox= new float[7], gyroy= new float[7], gyroz= new float[7];
            for(int i=0; i<7; i++){
                x[i] = floatArray[4 * i + 0];
                y[i] = floatArray[4 * i + 1];
                z[i] = floatArray[4 * i + 2];
                w[i] = floatArray[4 * i + 3];
                accx[i] = floatArray[3 * i + 28 + 0];
                accy[i] = floatArray[3 * i + 28 + 1];
                accz[i] = floatArray[3 * i + 28 + 2];
                gyrox[i] = floatArray[3 * i + 49 + 0];
                gyroy[i] = floatArray[3 * i + 49 + 1];
                gyroz[i] = floatArray[3 * i + 49 + 2];
            }

            //range = 腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节
            //float[] rangeUp = new float[] {110, 110, 110, 110, 110, 180, 180, 30, 30, 20, 20, 180, 180};
            //float[] rangeDown = new float[] { 70, 70, 70, 70, 70, 0, 0, 0, 0, 0, 0, 0, 0 };
            //float[] deltaRangeUp = new float[] { 5, 5, 5, 5, 5, 15, 15, 5, 5, 5, 5, 15, 15 };
            //float[] deltaRangeDown = new float[] { -5, -5, -5, -5, -5, -15, -15, -10, -10, -10, -10, -15, -15 };
            calSinglePartCalculationEx(floatArray, rangeUp, rangeDown, ref hermesNewCoreTest.isStarted, ref hermesNewCoreTest.tryToStartedCount, 
                                        ref hermesNewCoreTest.startedAngle, ref hermesNewCoreTest.tryToStopCount,
                                        deltaRangeUp, deltaRangeDown, ref hermesNewCoreTest.startList, ref hermesNewCoreTest.endList, ref hermesNewCoreTest.stableAngleList,
                                        ref hermesNewCoreTest.doudongList, ref hermesNewCoreTest.doudongListSum, lineIndex);

            m_jishiFlag = hermesNewCoreTest.isStarted;
            if(hermesNewCoreTest.isStarted == 1)
            {
                m_timeCount = (int)((lineIndex - (int)hermesNewCoreTest.startList[hermesNewCoreTest.startList.Count() - 1]) * ((float)10 / (float)g_SamplingRate));
                float zuodatuiDoudong = floatArray[3 * 1 + 49 + 0] * floatArray[3 * 1 + 49 + 0] + floatArray[3 * 1 + 49 + 1] * floatArray[3 * 1 + 49 + 1] + floatArray[3 * 1 + 49 + 2] * floatArray[3 * 1 + 49 + 2];
                float youdatuiDoudong = floatArray[3 * 2 + 49 + 0] * floatArray[3 * 2 + 49 + 0] + floatArray[3 * 2 + 49 + 1] * floatArray[3 * 2 + 49 + 1] + floatArray[3 * 2 + 49 + 2] * floatArray[3 * 2 + 49 + 2];
                float doudong = ((float)Math.Sqrt(zuodatuiDoudong) + (float)Math.Sqrt(youdatuiDoudong)) / 2.0F;
                hermesNewCoreTest.doudongListSum.Add(doudong);
            }
            else
            {
                m_timeCount = 0;
            }
            if(m_JINDUTIAO != 0)
            {
                if((float)m_timeCount / 10.0F / (float)m_JINDUTIAO * (float)g_SamplingRate > 1)
                {
                    m_jindutiao = 1;
                }
                else
                {
                    m_jindutiao = (float)m_timeCount / 10.0F / (float)m_JINDUTIAO * (float)g_SamplingRate;
                }
                
            }
            else
            {
                if(hermesNewCoreTest.isStarted == 0)
                {
                    m_jindutiao = (float)hermesNewCoreTest.tryToStartedCount/ (float)m_STARTCOUNTMAX;
                }
                else if(hermesNewCoreTest.isStarted == 1){
                    m_jindutiao = 1 - (float)hermesNewCoreTest.tryToStopCount / (float)m_STOPCOUNTMAX;
                }
                
            }
            if(m_timeCount <= 6200 && m_timeCount >= 6000  && hermesNewCoreTest.isStarted == 1 && m_index == TestMathodName.PilatesTrunkFlexion)
            {
                float[] tmp = hermesNewCoreTest.stableAngleList[hermesNewCoreTest.stableAngleList.Count() - 1];
                if(m_maxDuration < (tmp[7] + tmp[8]) / 2.0F)
                {
                    m_maxDuration = (tmp[7] + tmp[8]) / 2.0F;
                }
            }

            //Console.WriteLine("calculationSingleTime输出！");

            ////QListIterator<float> recordstartIteratorNew(*recordStartNew);
            //IEnumerator<float> recordstartIteratorNew = hermesTmp.recordStartNew.GetEnumerator();
            //////QListIterator<float> recordstopIteratorNew(*recordStopNew);
            //IEnumerator<float> recordstopIteratorNew = hermesTmp.recordStopNew.GetEnumerator();
            //////QListIterator<float> recordaverageIteratorNew(*recordAverageNew);
            //IEnumerator<float> recordaverageIteratorNew = hermesTmp.recordAverageNew.GetEnumerator();
            //while (recordaverageIteratorNew.MoveNext() && recordstopIteratorNew.MoveNext() && recordstartIteratorNew.MoveNext())
            //{
            //    float a = recordaverageIteratorNew.Current;
            //    float start = recordstartIteratorNew.Current;
            //    float stop = recordstopIteratorNew.Current;
            //    //qDebug("average: %f Start time: %f Stop time: %f Duration: %f", a, start, stop, stop - start);
            //    string msg = "lineIndex:" + lineIndex + "average" + ":" + a.ToString() + " Start time:" + start.ToString() + " Stop time:" + stop.ToString() + " Duration:" + (stop - start).ToString();
            //    Console.WriteLine(msg);
            //}
        }

        public int calResult(int lineIndex)
        {
            //200个点

            float[] floatArrayTmp = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];

            for (int iii = 0; iii < 7; iii++)
            {
                floatArrayTmp[4 * iii + 1] = 0F;
                floatArrayTmp[4 * iii + 2] = 1F;
                floatArrayTmp[4 * iii + 3] = 0F;
                floatArrayTmp[4 * iii + 0] = 0F;

                if (iii == 0)
                {
                    floatArrayTmp[4 * iii + 1] = 0.907F;
                    floatArrayTmp[4 * iii + 3] = (float)Math.Sqrt(1 - floatArrayTmp[4 * iii + 1] * floatArrayTmp[4 * iii + 1]);
                }

                if (iii == 3 || iii == 4)
                {
                    floatArrayTmp[4 * iii + 1] = 0.707F;
                }


                if (iii == 3 || iii == 4)
                {
                    floatArrayTmp[4 * iii + 3] = (float)Math.Sqrt(1 - floatArrayTmp[4 * iii + 1] * floatArrayTmp[4 * iii + 1]);
                }
                floatArrayTmp[3 * iii + 0 + 28] = 900;
                floatArrayTmp[3 * iii + 1 + 28] = 900;
                floatArrayTmp[3 * iii + 2 + 28] = 900;
                floatArrayTmp[3 * iii + 0 + 49] = 900;
                floatArrayTmp[3 * iii + 1 + 49] = 900;
                floatArrayTmp[3 * iii + 2 + 49] = 900;
            }


            for (int iiii = 0; iiii < 550; iiii++)
            {
                floatArrayTmp[4 * 7 + 3 * 7 + 3 * 7] = lineIndex + iiii;
                calculationSingleTime(floatArrayTmp, lineIndex + 10 + iiii);
            }

            startList.Clear();
            endList.Clear();


            totalStartList.Clear();
            totalEndList.Clear();

            float maxDuration = 0;
            IEnumerator<float> totalStartIterator = totalStartList.GetEnumerator();
            //QListIterator<float> subEndIterator(*subEndList);
            IEnumerator<float> totalEndIterator = totalEndList.GetEnumerator();
            while (totalStartIterator.MoveNext() && totalEndIterator.MoveNext())
            {
                float start = totalStartIterator.Current;
                float end = totalEndIterator.Current;
                if(maxDuration < (end - start))
                {
                    maxDuration = (end - start);
                }
            }

            float maxDurationEx = 0;
            if(hermesNewCoreTest.startList.Count() == hermesNewCoreTest.endList.Count() && hermesNewCoreTest.startList.Count() == hermesNewCoreTest.doudongList.Count())
            {
                for (int i = 0; i < hermesNewCoreTest.startList.Count(); i++)
                {
                    if (maxDurationEx < hermesNewCoreTest.endList[i] - hermesNewCoreTest.startList[i])
                    {
                        maxDurationEx = hermesNewCoreTest.endList[i] - hermesNewCoreTest.startList[i];
                        if(m_index == TestMathodName.V_Sit)
                        {
                            m_shaking = 100.0F - hermesNewCoreTest.doudongList[i] * 2.0F;
                        }
                        else if(m_index == TestMathodName.CoreFunctionalTest)
                        {
                            m_shaking = 100.0F - hermesNewCoreTest.doudongList[i] * 0.3F;
                        }
                        else if (m_index == TestMathodName.CoreFunctionalTestOpposite)
                        {
                            m_shaking = 100.0F - hermesNewCoreTest.doudongList[i] * 0.3F;
                        }
                        else
                        {
                            m_shaking = 100.0F - hermesNewCoreTest.doudongList[i] * 1.0F;
                        }
                        if (m_shaking <= 13)
                        {
                            Random ran = new Random();
                            m_shaking = (float)ran.Next(130, 150) / 10.0F;
                        }
                        else if (m_shaking > 100)
                        {
                            m_shaking = 100;
                        }
                        else if(m_shaking == float.NaN)
                        {
                            Random ran = new Random();
                            m_shaking = (float)ran.Next(130, 150) / 10.0F;
                        }
                    }
                }
            }
            if (m_index == TestMathodName.PilatesTrunkFlexion)
            {

            }
            else
            {
                if(m_maxDuration < maxDurationEx)
                {
                    m_maxDuration = maxDurationEx / 100.0F / (float)g_SamplingRate;
                }
            }
            return 0;
        }
    } //核心测试，主要类

    public class HermesSquatJumpTestBase
    {
        public bool isSquatOrNot;
        public double squatToStandMinAngle;
        public bool isJumpStartOrNot;
        public List<float> startRange;
        public bool gravityLostOrNot;
        public int footToGroundAccIncreseCount;
        public double footAccOld;
        public List<float> endRange;
        public static int squatDurationCountLeft;
        public static int squatDurationCountRight;
        public int squatDurationCount;
        public bool gravityLostOrNotFoot;
        public int lastStartTimeSave;

        public HermesSquatJumpTestBase()
        {
            isSquatOrNot = false;
            squatToStandMinAngle = 100.0;
            isJumpStartOrNot = false;
            startRange = new List<float>();
            gravityLostOrNot = false;
            footToGroundAccIncreseCount = 0;
            footAccOld = 0.0;
            endRange = new List<float>();
            squatDurationCount = 0;
            squatDurationCountLeft = 0;
            squatDurationCountRight = 0;
            gravityLostOrNotFoot = false;
            lastStartTimeSave = -1;
        }
        /*****************************************
        编写时间：2018.12.12
        功能：重置所有初始化值
        编写人：Kx.HU
        *********************************************/
        public void reset()
        {
            isSquatOrNot = false;
            squatToStandMinAngle = 100.0;
            isJumpStartOrNot = false;
            startRange.Clear();
            gravityLostOrNot = false;
            footToGroundAccIncreseCount = 0;
            footAccOld = 0.0;
            endRange.Clear();
            squatDurationCount = 0;
            squatDurationCountLeft = 0;
            squatDurationCountRight = 0;
            gravityLostOrNotFoot = false;
            lastStartTimeSave = -1;
        }
    }//下肢爆发力测试，基类，不要实例化

    public class HermesSquatJumpTest
    {
        //public static int dunStartAngle = 72;
        //public static float dunMinAngle = 8.0F;
        //public static float footToGroundAccMinDetect = 0.5F;
        //public static int squatDurationCountMax = 150;
        public static int g_SamplingRate;
        public int m_squatDurationCountMa_inline;
        public const float PI = 3.14159265358979323846F;
        public enum TestMathodName
        {
            ShenDunTiao = 0,
            ShenDunTiaoFree = 0
        }

        public HermesSquatJumpTestBase hermesSquatJumpTestExLeft;
        public HermesSquatJumpTestBase hermesSquatJumpTestExRight;
        public List<float> totalStartListLeft;
        public List<float> totalEndListLeft;
        public List<float> totalStartListRight;
        public List<float> totalEndListRight;

        public int m_dunStartAngle;
        public float m_dunMinAngle;
        public float m_footToGroundAccMinDetect;
        public int m_squatDurationCountMax;
        public float shakingSumLeft;
        public float shakingSumRight;


        //下蹲进度条
        public float m_jinDutiaoLeft;
        public float m_jinDutiaoRight;

        //抖动情况(0-100)
        public float m_shaking;
        //下蹲程度(0-100)
        public float m_squat;
        //左右侧对称性（0-100）
        public float m_balance;
        //动作标准性（0-100）
        public float m_standard;

        //是否采集成功（0：未采集到数据，1：采集到数据）
        public int m_jishiFlag;

        //关节和肢体检测状态变量
        public static string[] Parts = new string[] { "腰部", "左大腿", "右大腿", "左小腿", "右小腿", "左脚", "右脚", "左髋关节", "右髋关节", "左漆关节", "右膝关节", "左踝关节", "左踝关节" };
        public static string[] errorDetails = new string[] { "打弯", "扭转过大", "拱起", "下榻" };
        public List<Dictionary<string, float>> m_errors = new List<Dictionary<string, float>>();


        public HermesSquatJumpTest()
        {
            hermesSquatJumpTestExLeft = new HermesSquatJumpTestBase();
            hermesSquatJumpTestExRight = new HermesSquatJumpTestBase();
            totalStartListLeft = new List<float>();
            totalEndListLeft = new List<float>();
            totalStartListRight = new List<float>();
            totalEndListRight = new List<float>();
            m_jishiFlag = 0;
        }

        public void reset(TestMathodName index)
        {
            hermesSquatJumpTestExLeft.reset();
            hermesSquatJumpTestExRight.reset();
            totalStartListLeft.Clear();
            totalEndListLeft.Clear();
            totalStartListRight.Clear();
            totalEndListRight.Clear();

            m_shaking = 100.0F;
            m_squat = 0.0F;
            m_balance = 0.0F;
            m_standard = 0.0F;
            m_jishiFlag = 0;

            if (imudatareceiver_plus.m_SamplingRate == 400)
            {
                g_SamplingRate = 4;
            }
            else if (imudatareceiver_plus.m_SamplingRate == 100)
            {
                g_SamplingRate = 1;
            }

            if (index == TestMathodName.ShenDunTiao)
            {
                m_dunStartAngle = 72;
                m_dunMinAngle = 8.0F;
                m_footToGroundAccMinDetect = 0.5F;
                m_squatDurationCountMa_inline = 150 * g_SamplingRate;
            }
            else if (index == TestMathodName.ShenDunTiaoFree)
            {
                m_dunStartAngle = 72;
                m_dunMinAngle = 8.0F;
                m_footToGroundAccMinDetect = 0.5F;
                m_squatDurationCountMa_inline = 150 * g_SamplingRate;
            }
            else
            {
                m_dunStartAngle = 72;
                m_dunMinAngle = 8.0F;
                m_footToGroundAccMinDetect = 0.5F;
                m_squatDurationCountMa_inline = 150 * g_SamplingRate;
            }
        }

        public float reqMainAngleRelative(float w0, float x0, float y0, float z0, int direction0,
                           float w, float x, float y, float z, int direction)
        {
            float l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            switch (direction)
            {
                case 0:      //X方向
                    o = 1 - 2 * y * y - 2 * z * z;
                    p = 2 * x * y + 2 * w * z;
                    q = 2 * x * z - 2 * w * y;
                    break;
                case 1:      //Y方向
                    o = 2 * x * y - 2 * w * z;
                    p = 1 - 2 * x * x - 2 * z * z;
                    q = 2 * y * z + 2 * w * x;
                    break;
                case 2:      //Z方向
                    o = 2 * x * z + 2 * w * y;
                    p = 2 * y * z - 2 * w * x;
                    q = 1 - 2 * x * x - 2 * y * y;
                    break;
                default:
                    break;
            }
            //    float Angle = sqrt((m*q - n * p)*(m*q - n * p) + (n*o - l * q)*(n*o - l * q) + (l*p - m * o)*(l*p - m * o));
            //    Angle = asin(Angle) / PI * 180;
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }


        void calJumpTimeQuat(float w1, float x1, float y1, float z1, float w2, float x2, float y2, float z2, //膝盖
                     float w3, float x3, float y3, float z3, float w4, float x4, float y4, float z4, //脚
                     float gyrox_leg, float gyroy_leg, float gyroz_leg, float accx_leg, float accy_leg, float accz_leg,      //小腿
                     float gyrox_foot, float gyroy_foot, float gyroz_foot, float accx_foot, float accy_foot, float accz_foot,      //脚
                     ref bool isSquatOrNot, ref double squatToStandMinAngle, ref bool isJumpStartOrNot, ref bool gravityLostOrNot, ref bool gravityLostOrNotFoot,
                     ref int footToGroundAccIncreseCount, ref double footAccOld, ref int squatDurationCount, ref int squatDurationCountStatic,
                     ref List<float> startRange, ref List<float> endRange, ref int lastStartTimeSave,
                     int index)
        {

            float angle = reqMainAngleRelative(w1, x1, y1, z1, 2, w2, x2, y2, z2, 2);
            //#define dunStartAngle 60
            //#define dunMinAngle 8
            //#define footToGroundAccMinDetect 0.5
            //#define squatDurationCountMax 500
            //检测站起来
            if (angle < m_dunStartAngle && (isSquatOrNot == false || isJumpStartOrNot == false))
            {
                squatDurationCount = 0;
                footToGroundAccIncreseCount = 0;
                HermesSquatJumpTestBase.squatDurationCountRight  = 0;
                HermesSquatJumpTestBase.squatDurationCountLeft = 0;
                //gravityLostOrNot = false;
            }
            //检测下蹲开始
            if (angle > m_dunStartAngle && lastStartTimeSave == -1)
            {
                if (isSquatOrNot == false)
                {
                    squatDurationCount+=1;
                    squatDurationCountStatic+=1;
                }
                if (isSquatOrNot == false && squatDurationCount >= m_squatDurationCountMa_inline && 
                    HermesSquatJumpTestBase.squatDurationCountRight >= m_squatDurationCountMa_inline && HermesSquatJumpTestBase.squatDurationCountLeft >= m_squatDurationCountMa_inline)
                {
                    isSquatOrNot = true;
                    isJumpStartOrNot = false;
                    gravityLostOrNot = false;
                    gravityLostOrNotFoot = false;
                    footToGroundAccIncreseCount = 0;
                    squatDurationCount = m_squatDurationCountMa_inline + 5;
                    m_squat = angle/2.0F;
                }
            }

            //进度条设置
            if(HermesSquatJumpTestBase.squatDurationCountLeft <= m_squatDurationCountMa_inline && HermesSquatJumpTestBase.squatDurationCountLeft >= 0)
            {
                m_jinDutiaoLeft = (float)HermesSquatJumpTestBase.squatDurationCountLeft / (float)m_squatDurationCountMa_inline;
            }
            else if(HermesSquatJumpTestBase.squatDurationCountLeft < 0)
            {
                m_jinDutiaoLeft = 0;
            }else if(HermesSquatJumpTestBase.squatDurationCountLeft > m_squatDurationCountMa_inline)
            {
                m_jinDutiaoLeft = 1.00F;
            }

            //进度条设置
            if (HermesSquatJumpTestBase.squatDurationCountRight <= m_squatDurationCountMa_inline && HermesSquatJumpTestBase.squatDurationCountRight >= 0)
            {
                m_jinDutiaoRight= (float)HermesSquatJumpTestBase.squatDurationCountRight / (float)m_squatDurationCountMa_inline;
            }
            else if (HermesSquatJumpTestBase.squatDurationCountRight < 0)
            {
                m_jinDutiaoRight = 0;
            }
            else if (HermesSquatJumpTestBase.squatDurationCountRight > m_squatDurationCountMa_inline)
            {
                m_jinDutiaoRight = 1.00F;
            }

            //检测跳起打直
            if (isSquatOrNot == true)
            {
                if (angle < squatToStandMinAngle && angle < m_dunMinAngle + 3)
                {
                    squatToStandMinAngle = angle;
                }
                if (squatToStandMinAngle <= m_dunMinAngle-1)
                {
                    isSquatOrNot = false;
                    squatToStandMinAngle = 100.0;
                    isJumpStartOrNot = true;
                    startRange.Add(index);
                    lastStartTimeSave = index;
                }
                //此处添加跳跃不打直代偿情况
            }

            //if (index == 1331)
            //{
            //    int apple = 1;
            //}
            //跳跃开始,检测脚触地, 检查小腿经过一个失重状态
            double acc_foot = Math.Sqrt(accx_foot * accx_foot + accy_foot * accy_foot + accz_foot * accz_foot);
            if (isJumpStartOrNot == true || (lastStartTimeSave != -1 && index - lastStartTimeSave >= 100 * g_SamplingRate))
            {
                if ((lastStartTimeSave != -1 && index - lastStartTimeSave >= 100 * g_SamplingRate))
                {
                    endRange.Add(lastStartTimeSave);
                    isJumpStartOrNot = false;
                    gravityLostOrNot = false;
                    gravityLostOrNotFoot = false;
                    lastStartTimeSave = -1;
                }
                else
                {
                    double acc_leg = Math.Sqrt(accx_leg * accx_leg + accy_leg * accy_leg + accz_leg * accz_leg);
                    if (gravityLostOrNot == false && acc_leg < 0.25)
                    {
                        gravityLostOrNot = true;
                        //此处可以保存第一次失重的时间
                    }
                    if (gravityLostOrNotFoot == false && acc_foot < 0.45)
                    {
                        gravityLostOrNotFoot = true;
                    }
                    if (gravityLostOrNot == true && gravityLostOrNotFoot == true)
                    {
                        //开始检测脚触地时间（阈值检测法）

                        //开始检测脚触地时间（明显增量式检测法）
                        double delta = acc_foot - footAccOld;
                        if (delta > m_footToGroundAccMinDetect && acc_foot > 1.0)
                        {
                            endRange.Add(index);
                            isJumpStartOrNot = false;
                            gravityLostOrNot = false;
                            gravityLostOrNotFoot = false;
                            lastStartTimeSave = -1; 
                        }
                    }
                }
                
            }
            footAccOld = acc_foot;

            //String msg = "Start: ";
            //msg += index + " " + angle +" "+ hermesSquatJumpTestExLeft.isSquatOrNot + " " + hermesSquatJumpTestExLeft.squatToStandMinAngle + " " + hermesSquatJumpTestExLeft.squatDurationCount + " "
            //    + hermesSquatJumpTestExLeft.gravityLostOrNot + " " + hermesSquatJumpTestExLeft.isJumpStartOrNot + " ";
            //Console.WriteLine(msg);

        }

        public void calculationSingleTime(float[] float_array, int lineIndex)
        {

            float[] w = new float[7], x = new float[7], y = new float[7], z = new float[7], accx = new float[7], accy = new float[7], accz = new float[7], gyrox = new float[7], gyroy = new float[7], gyroz = new float[7];
            for (int i = 0; i < 7; i++)
            {
                x[i] = float_array[4 * i + 0];
                y[i] = float_array[4 * i + 1];
                z[i] = float_array[4 * i + 2];
                w[i] = float_array[4 * i + 3];
                accx[i] = float_array[3 * i + 28 + 0];
                accy[i] = float_array[3 * i + 28 + 1];
                accz[i] = float_array[3 * i + 28 + 2];
                gyrox[i] = float_array[3 * i + 49 + 0];
                gyroy[i] = float_array[3 * i + 49 + 1];
                gyroz[i] = float_array[3 * i + 49 + 2];
            }

            if(HermesSquatJumpTestBase.squatDurationCountLeft >= 80 && HermesSquatJumpTestBase.squatDurationCountLeft <= 130)
            {
                shakingSumLeft += (float)Math.Sqrt(gyrox[1] * gyrox[1] + gyroy[1] * gyroy[1] + gyroz[1] * gyroz[1]);
            }else if (HermesSquatJumpTestBase.squatDurationCountLeft <= 90)
            {
                shakingSumLeft = 0;
            }

            if (HermesSquatJumpTestBase.squatDurationCountRight >= 80 && HermesSquatJumpTestBase.squatDurationCountRight <= 130)
            {
                shakingSumRight += (float)Math.Sqrt(gyrox[2] * gyrox[2] + gyroy[2] * gyroy[2] + gyroz[2] * gyroz[2]);
            }
            else if (HermesSquatJumpTestBase.squatDurationCountRight <= 90)
            {
                shakingSumRight = 0;
            }

            if ((HermesSquatJumpTestBase.squatDurationCountLeft >= 140 && HermesSquatJumpTestBase.squatDurationCountLeft <= 143) && (HermesSquatJumpTestBase.squatDurationCountRight >= 140 && HermesSquatJumpTestBase.squatDurationCountRight <= 143))
            {
                float shaking_tmp = (shakingSumLeft + shakingSumRight) / 2.0F /50F * 4F;
                if(shaking_tmp > 100.0F)
                {
                    Random ran = new Random();
                    int RandKey = ran.Next(1, 99);
                    m_shaking = (float)RandKey/10.0F;
                    //Console.WriteLine("超范围!");
                }
                else
                {
                    m_shaking = 100 - shaking_tmp;
                    //Console.WriteLine("没超范围!");
                }

                if (m_shaking > 100)
                {
                    m_shaking = 100;
                }
                else if (m_shaking == float.NaN)
                {
                    Random ran = new Random();
                    m_shaking = (float)ran.Next(130, 150) / 10.0F;
                }
            }

            int leftFoot = 5, rightFoot = 6;

            calJumpTimeQuat(w[1], x[1], y[1], z[1], w[3], x[3], y[3], z[3],
                            w[leftFoot], x[leftFoot], y[leftFoot], z[leftFoot], 1, 0, 0, 0,
                            gyrox[1], gyroy[1], gyroz[1], accx[1], accy[1], accz[1],
                            gyrox[leftFoot], gyroy[leftFoot], gyroz[leftFoot], accx[leftFoot], accy[leftFoot], accz[leftFoot],
                            ref hermesSquatJumpTestExLeft.isSquatOrNot, ref hermesSquatJumpTestExLeft.squatToStandMinAngle, ref hermesSquatJumpTestExLeft.isJumpStartOrNot,
                            ref hermesSquatJumpTestExLeft.gravityLostOrNot, ref hermesSquatJumpTestExLeft.gravityLostOrNotFoot,
                            ref hermesSquatJumpTestExLeft.footToGroundAccIncreseCount, ref hermesSquatJumpTestExLeft.footAccOld, ref hermesSquatJumpTestExLeft.squatDurationCount, ref HermesSquatJumpTestBase.squatDurationCountLeft,
                            ref hermesSquatJumpTestExLeft.startRange, ref hermesSquatJumpTestExLeft.endRange, ref hermesSquatJumpTestExLeft.lastStartTimeSave, lineIndex
                            );

            ////        qDebug() << lineIndex << hermesSquatJumpTestExLeft->isSquatOrNot << hermesSquatJumpTestExLeft->squatToStandMinAngle << hermesSquatJumpTestExLeft->squatDurationCount
            ////                 << hermesSquatJumpTestExLeft->gravityLostOrNot << hermesSquatJumpTestExLeft->isJumpStartOrNot;
            //String msg = "Start: ";
            //msg += lineIndex + " " + hermesSquatJumpTestExLeft.isSquatOrNot + " " + hermesSquatJumpTestExLeft.squatToStandMinAngle + " " + hermesSquatJumpTestExLeft.squatDurationCount + " " 
            //    + hermesSquatJumpTestExLeft.gravityLostOrNot + " " + hermesSquatJumpTestExLeft.isJumpStartOrNot + " ";
            //Console.WriteLine(msg);

            calJumpTimeQuat(w[2], x[2], y[2], z[2], w[4], x[4], y[4], z[4],
                            w[rightFoot], x[rightFoot], y[rightFoot], z[rightFoot], 1, 0, 0, 0,
                            gyrox[2], gyroy[2], gyroz[2], accx[2], accy[2], accz[2],
                            gyrox[rightFoot], gyroy[rightFoot], gyroz[rightFoot], accx[rightFoot], accy[rightFoot], accz[rightFoot],
                            ref hermesSquatJumpTestExRight.isSquatOrNot, ref hermesSquatJumpTestExRight.squatToStandMinAngle, ref hermesSquatJumpTestExRight.isJumpStartOrNot,
                            ref hermesSquatJumpTestExRight.gravityLostOrNot, ref hermesSquatJumpTestExRight.gravityLostOrNotFoot,
                            ref hermesSquatJumpTestExRight.footToGroundAccIncreseCount, ref hermesSquatJumpTestExRight.footAccOld, ref hermesSquatJumpTestExRight.squatDurationCount, ref HermesSquatJumpTestBase.squatDurationCountRight,
                            ref hermesSquatJumpTestExRight.startRange, ref hermesSquatJumpTestExRight.endRange, ref hermesSquatJumpTestExRight.lastStartTimeSave, lineIndex
                            );

            //循环判断，左脚取值，判断右脚情况
            bool trueValue = false;
            int limitedTime = 15;
            int jishiTMP = 0;
            //m_jishiFlag = 0;
            if (hermesSquatJumpTestExLeft.startRange.Count() == hermesSquatJumpTestExLeft.endRange.Count()
                    && hermesSquatJumpTestExRight.startRange.Count() == hermesSquatJumpTestExRight.endRange.Count())
            {

                for (int i = 0; i < hermesSquatJumpTestExLeft.startRange.Count(); i++)
                {
                    float startTimeStampLeft = hermesSquatJumpTestExLeft.startRange[i];
                    float endTimeStampLeft = hermesSquatJumpTestExLeft.endRange[i];

                    for (int j = 0; j < hermesSquatJumpTestExRight.startRange.Count(); j++)
                    {
                        float startTimeStampRight = hermesSquatJumpTestExRight.startRange[j];
                        float endTimeStampRight = hermesSquatJumpTestExRight.endRange[j];

                        if (startTimeStampLeft <= startTimeStampRight + limitedTime && startTimeStampLeft >= startTimeStampRight - limitedTime
                                && endTimeStampLeft <= endTimeStampRight + limitedTime && endTimeStampLeft >= endTimeStampRight - limitedTime 
                                && startTimeStampLeft != endTimeStampLeft && startTimeStampRight != endTimeStampLeft)
                        {
                            trueValue = true;
                            jishiTMP++;
                        }
                    }
                }
            }
            if (trueValue == true)
            {
                m_jishiFlag = jishiTMP;
            }
        }

        public int calResult()
        {
            int limitedTime = 15;
            totalStartListLeft.Clear();
            totalStartListRight.Clear();
            totalEndListLeft.Clear();
            totalEndListRight.Clear();
            //循环判断，左脚取值，判断右脚情况
            bool trueValue = false;
            if (hermesSquatJumpTestExLeft.startRange.Count() == hermesSquatJumpTestExLeft.endRange.Count()
                    && hermesSquatJumpTestExRight.startRange.Count() == hermesSquatJumpTestExRight.endRange.Count())
            {

                for (int i = 0; i < hermesSquatJumpTestExLeft.startRange.Count(); i++)
                {
                    float startTimeStampLeft = hermesSquatJumpTestExLeft.startRange[i];
                    float endTimeStampLeft = hermesSquatJumpTestExLeft.endRange[i];

                    for (int j = 0; j < hermesSquatJumpTestExRight.startRange.Count(); j++)
                    {
                        float startTimeStampRight = hermesSquatJumpTestExRight.startRange[j];
                        float endTimeStampRight = hermesSquatJumpTestExRight.endRange[j];

                        if (startTimeStampLeft <= startTimeStampRight + limitedTime && startTimeStampLeft >= startTimeStampRight - limitedTime
                                && endTimeStampLeft <= endTimeStampRight + limitedTime && endTimeStampLeft >= endTimeStampRight - limitedTime
                                 && startTimeStampLeft != endTimeStampLeft && startTimeStampRight != endTimeStampLeft)
                        {
                            totalStartListLeft.Add(hermesSquatJumpTestExLeft.startRange[i]);
                            totalStartListRight.Add(hermesSquatJumpTestExRight.startRange[j]);
                            totalEndListLeft.Add(hermesSquatJumpTestExLeft.endRange[i]);
                            totalEndListRight.Add(hermesSquatJumpTestExRight.endRange[j]);
                            trueValue = true;
                        }
                    }
                }
            }
            if (trueValue == true)
            {
                float maxJumpCount = 0;
                float deltaPian = 0;
                //float maxJumpCountRight = 0;
                //qDebug() << "左脚" << *totalStartListLeft << *totalEndListLeft << "右脚" << *totalStartListRight << *totalEndListRight;
                if (totalStartListLeft.Count() == totalEndListLeft.Count()  && totalStartListRight.Count() == totalEndListRight.Count()  && totalStartListRight.Count() == totalStartListLeft.Count())
                {
                    for (int i = 0; i < totalStartListLeft.Count; i++)
                    {
                        float startTimeTmpLeft = totalStartListLeft[i];
                        float endTimeTmpLeft = totalEndListLeft[i];

                        float startTimeTmpRight = totalStartListRight[i];
                        float endTimeTmpRight = totalEndListRight[i];

                        float averageTmp = ((endTimeTmpLeft - startTimeTmpLeft) + (endTimeTmpRight - startTimeTmpRight)) / 2.0F;

                        if (averageTmp > maxJumpCount)
                        {
                            maxJumpCount = averageTmp;
                            deltaPian = Math.Abs(Math.Abs(endTimeTmpLeft - endTimeTmpRight) + Math.Abs(startTimeTmpLeft - startTimeTmpRight));
                        }
                    }
                }

                m_squatDurationCountMax = (int)(((int)maxJumpCount - 5 * g_SamplingRate) / (float)g_SamplingRate);
                if(m_squatDurationCountMax < 0)
                {
                    m_squatDurationCountMax = 0;
                }
                Random ran = new Random();
                int RandKey = ran.Next(10, 50);
                m_balance = 100 - deltaPian * 5 - (float)RandKey/10.0F;

                return 1;
            }
            //qDebug() << "计算失败";
            return -1;
        }

    }  //下肢爆发力测试，主要类

    public class HermesBalanceTestBaseEx
    {
        public int isStarted;
        public int tryToStartedCount;
        public float[] startedAngle = new float[13];
        public int tryToStopCount;
        public List<float> startList;
        public List<float> endList;
        public List<float[]> stableAngleList;
        public List<float> doudongList;
        public List<float> doudongListSum;
        public float squatMaxAngle;
        public int tryToStableValueCount;

        public HermesBalanceTestBaseEx()
        {
            isStarted = 0;
            tryToStartedCount = 0;
            tryToStopCount = 0;
            for (int i = 0; i < 13; i++)
            {
                startedAngle[i] = 0;
            }
            startList = new List<float>();
            endList = new List<float>();
            stableAngleList = new List<float[]>();
            doudongList = new List<float>();
            doudongListSum = new List<float>();
            squatMaxAngle = 0;
            tryToStableValueCount = 0;
        }
        /*****************************************
        编写时间：2018.12.12
        功能：重置所有初始化值
        编写人：Kx.HU
        *********************************************/
        public void reset()
        {
            isStarted = 0;
            tryToStartedCount = 0;
            for (int i = 0; i < 13; i++)
            {
                startedAngle[i] = 0;
            }
            tryToStopCount = 0;
            startList.Clear();
            endList.Clear();
            stableAngleList.Clear();
            doudongList.Clear();
            doudongListSum.Clear();
            squatMaxAngle = 0;
            tryToStableValueCount = 0;
        }
    } //平衡性测试，基类，不要实例化

    public class HermesBalanceTest
    {
        public const float PI = 3.14159265358979323846F;
        public static int g_SamplingRate;

        public int m_STARTCOUNTMAX;
        public int m_STOPCOUNTMAX;
        public int m_DECREASERATE;
        public int m_JINDUTIAO;

        //边界情况
        public float[] rangeUp = new float[] { 110, 110, 110, 110, 110, 180, 180, 30, 30, 30, 30, 180, 180 };
        public float[] rangeDown = new float[] { 70, 80, 80, 85, 85, 90, 90, 0, 0, 0, 0, 0, 0 };
        public float[] deltaRangeUp = new float[] { 5, 10, 10, 10, 10, 30, 30, 5, 5, 5, 5, 15, 15 };
        public float[] deltaRangeDown = new float[] { -5, -10, -10, -10, -10, -30, -30, -5, -5, -5, -5, -15, -15 };

        //抖动情况(0-100)
        public float m_shaking;
        //动作标准性(0-100)
        public float m_standard;
        //腰部倾斜情况(0-100)
        public float m_incline;
        //左右腿平衡度(0-100)
        public float m_balance;

        //是否开始计时（0：没有开始，1：计时中）
        public int m_jishiFlag;
        //计时累计时间（单位毫秒）
        public int m_timeCount;
        //计时进度条(0-1)
        public float m_jindutiao;
        //最大持续时间（单位10毫秒）
        public float m_maxDuration;

        //姿态和关节检测（0是正常，1是异常，顺序：腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节）
        public int[] m_angleAndJointDetectFlag = new int[13];
        //姿态和关节不稳定检测（0是正常，1是异常，顺序：腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节）
        public int[] m_angleAndJointDetectUnstableFlag = new int[13];
        //当前关节值
        public float[] m_angleAndJointCurrentValue = new float[13];
        ////边界情况
        //public float[] rangeUp = new float[13];
        //public float[] rangeDown = new float[13];
        //public float[] deltaRangeUp = new float[13];
        //public float[] deltaRangeDown = new float[13];

        //关节和肢体检测状态变量
        public static string[] Parts = new string[] { "腰部", "左大腿", "右大腿", "左小腿", "右小腿", "左脚", "右脚", "左髋关节", "右髋关节", "左漆关节", "右膝关节", "左踝关节", "左踝关节" };
        public static string[] errorDetails = new string[] { "打弯", "扭转过大", "拱起", "下榻" };
        public List<Dictionary<string, float>> m_errors = new List<Dictionary<string, float>>();

        public TestMathodName m_index;

        public enum TestMathodName
        {
            BalanceTestStatic1Left = 0,
            BalanceTestStatic2Left = 1,
            BalanceTestStaticBlind1Left = 2,
            BalanceTestStaticBlind2Left = 3,
            BalanceTestStatic1Right = 4,
            BalanceTestStatic2Right = 5,
            BalanceTestStaticBlind1Right = 6,
            BalanceTestStaticBlind2Right = 7,
            BalanceTestDynamic1Left = 8,
            BalanceTestDynamic1Right = 9,
            PlankTest = 11,
            FeiYanShi = 12,
            CoreFunctionalTest = 13,
            CoreFunctionalTestOpposite = 14,
            V_Sit = 15,
        }

        public HermesBalanceTestBaseEx hermesNewBalanceTest;

        public List<List<float>> startList;
        public List<List<float>> endList;
        public List<float> totalStartList;
        public List<float> totalEndList;

        public HermesBalanceTest()
        {

            hermesNewBalanceTest = new HermesBalanceTestBaseEx(); hermesNewBalanceTest.reset();

            startList = new List<List<float>>();
            endList = new List<List<float>>();
            totalStartList = new List<float>();
            totalEndList = new List<float>();
            m_maxDuration = 0;
        }

        public void reset(TestMathodName index)
        {
            startList.Clear();
            endList.Clear();
            totalStartList.Clear();
            totalEndList.Clear();
            m_maxDuration = 0;
            hermesNewBalanceTest.reset();
            m_errors.Clear();

            m_shaking = 0.0F;
            m_standard = 0.0F;
            m_incline = 0.0F;
            m_balance = 0.0f;

            m_index = index;

            if (imudatareceiver_plus.m_SamplingRate == 400)
            {
                g_SamplingRate = 4;
            }
            else if (imudatareceiver_plus.m_SamplingRate == 100)
            {
                g_SamplingRate = 1;
            }

            if (index == TestMathodName.BalanceTestStatic1Right)
            {
                rangeUp = new float[] { 25, 25, 40, 25, 110, 180, 180, 25, 50, 25, 120, 180, 180 };
                rangeDown = new float[] { 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 60, 0, 0 };
                deltaRangeUp = new float[] { 8, 8, 15, 8, 15, 40, 40, 8, 15, 8, 35, 40, 40 };
                deltaRangeDown = new float[] { -8, -8, -15, -8, -15, -40, -40, -8, -15, -8, -15, -40, -40 };

                m_STARTCOUNTMAX = 200 * g_SamplingRate;
                m_STOPCOUNTMAX = 150 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.BalanceTestStaticBlind1Right)
            {
                rangeUp = new float[] { 25, 25, 40, 25, 110, 180, 180, 25, 50, 25, 120, 180, 180 };
                rangeDown = new float[] { 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 60, 0, 0 };
                deltaRangeUp = new float[] { 8, 8, 15, 8, 15, 40, 40, 8, 15, 8, 35, 40, 40 };
                deltaRangeDown = new float[] { -8, -8, -15, -8, -15, -40, -40, -8, -15, -8, -15, -40, -40 };

                m_STARTCOUNTMAX = 200 * g_SamplingRate;
                m_STOPCOUNTMAX = 150 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.BalanceTestStatic1Left)
            {
                rangeUp = new float[] { 25, 40, 25, 110, 25, 180, 180, 50, 25, 120, 25, 180, 180 };
                rangeDown = new float[] { 0, 0, 0, 55, 0, 0, 0, 0, 0, 60, 0, 0, 0 };
                deltaRangeUp = new float[] { 8, 15, 8, 15, 8, 40, 40, 15, 8, 35, 8, 40, 40 };
                deltaRangeDown = new float[] { -8, -15, -8, -15, -8, -40, -40, -15, -8, -15, -8, -40, -40 };

                m_STARTCOUNTMAX = 200 * g_SamplingRate;
                m_STOPCOUNTMAX = 150 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.BalanceTestStaticBlind1Left)
            {
                rangeUp = new float[] { 25, 40, 25, 110, 25, 180, 180, 50, 25, 120, 25, 180, 180 };
                rangeDown = new float[] { 0, 0, 0, 55, 0, 0, 0, 0, 0, 60, 0, 0, 0 };
                deltaRangeUp = new float[] { 8, 15, 8, 15, 8, 40, 40, 15, 8, 35, 8, 40, 40 };
                deltaRangeDown = new float[] { -8, -15, -8, -15, -8, -40, -40, -15, -8, -15, -8, -40, -40 };

                m_STARTCOUNTMAX = 200 * g_SamplingRate;
                m_STOPCOUNTMAX = 150 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.BalanceTestStatic2Right)
            {
                rangeUp = new float[] { 25, 25, 120, 25, 90, 180, 180, 25, 120, 25, 150, 180, 180 };
                rangeDown = new float[] { 0, 0, 40, 0, 15, 0, 0, 0, 30, 0, 40, 0, 0 };
                deltaRangeUp = new float[] { 8, 8, 25, 8, 25, 40, 40, 8, 25, 8, 35, 40, 40 };
                deltaRangeDown = new float[] { -8, -8, -15, -8, -15, -40, -40, -8, -15, -8, -15, -40, -40 };

                m_STARTCOUNTMAX = 200 * g_SamplingRate;
                m_STOPCOUNTMAX = 150 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.BalanceTestStaticBlind2Right)
            {
                rangeUp = new float[] { 25, 25, 120, 25, 90, 180, 180, 25, 120, 25, 150, 180, 180 };
                rangeDown = new float[] { 0, 0, 40, 0, 15, 0, 0, 0, 30, 0, 40, 0, 0 };
                deltaRangeUp = new float[] { 8, 8, 25, 8, 25, 40, 40, 8, 25, 8, 35, 40, 40 };
                deltaRangeDown = new float[] { -8, -8, -15, -8, -15, -40, -40, -8, -15, -8, -15, -40, -40 };

                m_STARTCOUNTMAX = 200 * g_SamplingRate;
                m_STOPCOUNTMAX = 150 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.BalanceTestStatic2Left)
            {
                rangeUp = new float[] { 25, 120, 25, 90, 25, 180, 180, 120, 25, 150, 25, 180, 180 };
                rangeDown = new float[] { 0, 40, 0, 15, 0, 0, 0, 30, 0, 40, 0, 0, 0 };
                deltaRangeUp = new float[] { 8, 25, 8, 25, 8, 40, 40, 25, 8, 35, 8, 40, 40 };
                deltaRangeDown = new float[] { -8, -15, -8, -15, -8, -40, -40, -15, -8, -15, -8, -40, -40 };

                m_STARTCOUNTMAX = 200 * g_SamplingRate;
                m_STOPCOUNTMAX = 150 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.BalanceTestStaticBlind2Left)
            {
                rangeUp = new float[] { 25, 120, 25, 90, 25, 180, 180, 120, 25, 150, 25, 180, 180 };
                rangeDown = new float[] { 0, 40, 0, 15, 0, 0, 0, 30, 0, 40, 0, 0, 0 };
                deltaRangeUp = new float[] { 8, 25, 8, 25, 8, 40, 40, 25, 8, 35, 8, 40, 40 };
                deltaRangeDown = new float[] { -8, -15, -8, -15, -8, -40, -40, -15, -8, -15, -8, -40, -40 };

                m_STARTCOUNTMAX = 200 * g_SamplingRate;
                m_STOPCOUNTMAX = 150 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.BalanceTestDynamic1Right)
            {

                rangeUp = new float[] { 120, 170, 170, 170, 170, 160, 160, 130, 130, 35, 35, 180, 180 };
                rangeDown = new float[] { 30, 95, 95, 95, 95, 70, 70, 0, 0, 0, 0, 0, 0 };
                //deltaRangeUp =   new float[] { +8, +15, +15, +15, +15, +50, +50, +15, +15,  +6,  +6, +50, +50 };
                //deltaRangeDown = new float[] { -8,  -6,  -6,  -6,  -6, -50, -50,  -6,  -6, -20, -20, -50, -50 };
                deltaRangeUp = new float[] { +8, +15, +15, +15, +15, +50, +50, +15, +15, +12, +12, +50, +50 };
                deltaRangeDown = new float[] { -8, -10, -10, -10, -10, -50, -50, -12, -12, -20, -20, -50, -50 };

                m_STARTCOUNTMAX = 100 * g_SamplingRate;
                m_STOPCOUNTMAX = 100 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
            else if (index == TestMathodName.BalanceTestDynamic1Left)
            {

                rangeUp = new float[] { 120, 170, 170, 170, 170, 160, 160, 130, 130, 35, 35, 180, 180 };
                rangeDown = new float[] { 30, 95, 95, 95, 95, 70, 70, 0, 0, 0, 0, 0, 0 };
                //deltaRangeUp =   new float[] { +8, +15, +15, +15, +15, +50, +50, +15, +15,  +6,  +6, +50, +50 };
                //deltaRangeDown = new float[] { -8,  -6,  -6,  -6,  -6, -50, -50,  -6,  -6, -20, -20, -50, -50 };
                deltaRangeUp = new float[] { +8, +15, +15, +15, +15, +50, +50, +15, +15, +12, +12, +50, +50 };
                deltaRangeDown = new float[] { -8, -10, -10, -10, -10, -50, -50, -12, -12, -20, -20, -50, -50 };

                m_STARTCOUNTMAX = 100 * g_SamplingRate;
                m_STOPCOUNTMAX = 100 * g_SamplingRate;
                m_DECREASERATE = 1;
                m_JINDUTIAO = 0;
            }
        }

        public float reqMainAngleRelative(float w0, float x0, float y0, float z0, int direction0,
                           float w, float x, float y, float z, int direction)
        {
            float l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            switch (direction)
            {
                case 0:      //X方向
                    o = 1 - 2 * y * y - 2 * z * z;
                    p = 2 * x * y + 2 * w * z;
                    q = 2 * x * z - 2 * w * y;
                    break;
                case 1:      //Y方向
                    o = 2 * x * y - 2 * w * z;
                    p = 1 - 2 * x * x - 2 * z * z;
                    q = 2 * y * z + 2 * w * x;
                    break;
                case 2:      //Z方向
                    o = 2 * x * z + 2 * w * y;
                    p = 2 * y * z - 2 * w * x;
                    q = 1 - 2 * x * x - 2 * y * y;
                    break;
                default:
                    break;
            }
            //    float Angle = sqrt((m*q - n * p)*(m*q - n * p) + (n*o - l * q)*(n*o - l * q) + (l*p - m * o)*(l*p - m * o));
            //    Angle = asin(Angle) / PI * 180;
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        void calSinglePartCalculationEx(float[] fArray, float[] rangeUp, float[] rangeDown, ref int isStarted, ref int tryToStartedCount, ref float[] startedAngle, ref int tryToStopCount,
                                        float[] deltaRangeUp, float[] deltaRangeDown, ref List<float> startList, ref List<float> endList, ref List<float[]> stableAngleList,
                                        ref List<float> doudongList, ref List<float> doudongListSum, int lineIndex)
        {
            //x[i] = float_array[4 * i + 0];
            //y[i] = float_array[4 * i + 1];
            //z[i] = float_array[4 * i + 2];
            //w[i] = float_array[4 * i + 3];
            //accx[i] = float_array[3 * i + 28 + 0];
            //accy[i] = float_array[3 * i + 28 + 1];
            //accz[i] = float_array[3 * i + 28 + 2];
            //gyrox[i] = float_array[3 * i + 49 + 0];
            //gyroy[i] = float_array[3 * i + 49 + 1];
            //gyroz[i] = float_array[3 * i + 49 + 2];
            //参数计算
            //range = 腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节

            float[] angle = new float[13];
            int index = 0;
            angle[0] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 1;
            angle[1] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 2;
            angle[2] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 3;
            angle[3] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 4;
            angle[4] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 5;
            angle[5] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 6;
            angle[6] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);

            int index1 = 0, index2 = 1;
            angle[7] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 0; index2 = 2;
            angle[8] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 1; index2 = 3;
            angle[9] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 2; index2 = 4;
            angle[10] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 3; index2 = 5;
            angle[11] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 4; index2 = 6;
            angle[12] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);

            //尝试进入计时状态
            //range = 腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节
            //m_STARTCOUNTMAX = 300;
            //m_STOPCOUNTMAX = 200;
            //m_DECREASERATE = 2;
            Random ran = new Random();

            //显示错误信息
            if (m_index == TestMathodName.BalanceTestStatic2Left || m_index == TestMathodName.BalanceTestStaticBlind2Left ||
                m_index == TestMathodName.BalanceTestStatic1Left || m_index == TestMathodName.BalanceTestStaticBlind1Left)
            {
                if (lineIndex % (100 * g_SamplingRate) == 0)
                {
                    m_errors.Clear();
                    if (angle[10] > 15)
                    {
                        Dictionary<string, float> err1 = new Dictionary<string, float>();
                        err1.Add("Part", 10);  //  右漆关节
                        err1.Add("Level", angle[10] - 15);
                        err1.Add("Detail", 0); // 打弯
                        m_errors.Add(err1);
                    }
                }
            }
            else if (m_index == TestMathodName.BalanceTestStatic2Right || m_index == TestMathodName.BalanceTestStaticBlind2Right ||
                     m_index == TestMathodName.BalanceTestStatic1Right || m_index == TestMathodName.BalanceTestStaticBlind1Right)
            {
                if (lineIndex % (100 * g_SamplingRate) == 0)
                {
                    m_errors.Clear();
                    if (angle[11] > 15)
                    {
                        Dictionary<string, float> err1 = new Dictionary<string, float>();
                        err1.Add("Part", 9);  //  左漆关节
                        err1.Add("Level", angle[9] - 15);
                        err1.Add("Detail", 0); // 打弯
                        m_errors.Add(err1);
                    }
                }
            }

            for (int i = 0; i < 13; i++)
            {
                m_angleAndJointCurrentValue[i] = angle[i];
            }

            int a = 0;
            if (lineIndex == 4600)
            {
                a = 1;
            }

            int allInRangeCount = 0;
            for (int i = 0; i < 13; i++)
            {
                if (angle[i] <= rangeUp[i] && angle[i] >= rangeDown[i])
                {
                    allInRangeCount++;
                    m_angleAndJointDetectFlag[i] = 0;
                }
                else
                {
                    m_angleAndJointDetectFlag[i] = 1;
                }
            }

            //如果静态平衡2动作，大腿侧向角度不够，不能进入计时状态
            if (allInRangeCount >= 13 && (m_index == TestMathodName.BalanceTestStatic2Left || m_index == TestMathodName.BalanceTestStaticBlind2Left) && isStarted == 0)
            {
                //float angle_tmp = reqMainAngleRelative(fArray[4 * 1 + 3], fArray[4 * 1 + 0], fArray[4 * 1 + 1], fArray[4 * 1 + 2], 0,
                //                                       fArray[4 * 2 + 3], fArray[4 * 2 + 0], fArray[4 * 2 + 1], fArray[4 * 2 + 2], 0);

                double w0, x0, y0, z0;
                double w1, x1, y1, z1;
                w0 = fArray[4 * 3 + 3]; x0 = fArray[4 * 3 + 0]; y0 = fArray[4 * 3 + 1]; z0 = fArray[4 * 3 + 2];
                w1 = fArray[4 * 4 + 3]; x1 = fArray[4 * 4 + 0]; y1 = fArray[4 * 4 + 1]; z1 = fArray[4 * 4 + 2];
                //Y方向 - 0
                double l0, m0, n0;
                l0 = 2 * x0 * y0 - 2 * w0 * z0;
                m0 = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                n0 = 0;
                //Y方向 - 1
                double l1, m1, n1;
                l1 = 2 * x1 * y1 - 2 * w1 * z1;
                m1 = 1 - 2 * x1 * x1 - 2 * z1 * z1;
                n1 = 0;
                //角度
                double inner = (l0 * l1 + m0 * m1 + n0 * n1) / Math.Sqrt(l0 * l0 + m0 * m0 + n0 * n0) / Math.Sqrt(l1 * l1 + m1 * m1 + n1 * n1);
                if (inner > 1.000) inner = 1.000F;
                else if (inner < -1.000) inner = -1.000F;
                float angle_tmp = (float)Math.Acos(inner) / PI * 180;

                if (angle_tmp < 50)
                {
                    return;
                }

                //if (lineIndex % (20 * g_SamplingRate) == 0)
                //{
                //    string msg = angle_tmp.ToString() + " " + l1 / Math.Sqrt(l1 * l1 + m1 * m1 + n1 * n1) + " " + m1 / Math.Sqrt(l1 * l1 + m1 * m1 + n1 * n1) +
                //    " " + l0 / Math.Sqrt(l0 * l0 + m0 * m0 + n0 * n0) + " " + m0 / Math.Sqrt(l0 * l0 + m0 * m0 + n0 * n0) + "\n";
                //    Console.WriteLine(msg);
                //}
            }
            else if (allInRangeCount >= 13 && (m_index == TestMathodName.BalanceTestStatic2Right || m_index == TestMathodName.BalanceTestStaticBlind2Right) && isStarted == 0)
            {
                double w0, x0, y0, z0;
                double w1, x1, y1, z1;
                w0 = fArray[4 * 3 + 3]; x0 = fArray[4 * 3 + 0]; y0 = fArray[4 * 3 + 1]; z0 = fArray[4 * 3 + 2];
                w1 = fArray[4 * 4 + 3]; x1 = fArray[4 * 4 + 0]; y1 = fArray[4 * 4 + 1]; z1 = fArray[4 * 4 + 2];
                //Y方向 - 0
                double l0, m0, n0;
                l0 = 2 * x0 * y0 - 2 * w0 * z0;
                m0 = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                n0 = 0;
                //Y方向 - 1
                double l1, m1, n1;
                l1 = 2 * x1 * y1 - 2 * w1 * z1;
                m1 = 1 - 2 * x1 * x1 - 2 * z1 * z1;
                n1 = 0;
                //角度
                double inner = (l0 * l1 + m0 * m1 + n0 * n1) / Math.Sqrt(l0 * l0 + m0 * m0 + n0 * n0) / Math.Sqrt(l1 * l1 + m1 * m1 + n1 * n1);
                if (inner > 1.000) inner = 1.000F;
                else if (inner < -1.000) inner = -1.000F;
                float angle_tmp = (float)Math.Acos(inner) / PI * 180;

                if (angle_tmp < 50)
                {
                    return;
                }

                //if (lineIndex % (20 * g_SamplingRate) == 0)
                //{
                //    string msg = angle_tmp.ToString() + " " + l1 / Math.Sqrt(l1 * l1 + m1 * m1 + n1 * n1) + " " + m1 / Math.Sqrt(l1 * l1 + m1 * m1 + n1 * n1) +
                //    " " + l0 / Math.Sqrt(l0 * l0 + m0 * m0 + n0 * n0) + " " + m0 / Math.Sqrt(l0 * l0 + m0 * m0 + n0 * n0) + "\n";
                //    Console.WriteLine(msg);
                //}
            }


            if (allInRangeCount >= 13 && isStarted == 0)
            {
                if (tryToStartedCount >= m_STARTCOUNTMAX)
                {
                    tryToStartedCount = m_STARTCOUNTMAX;
                }
                else
                {
                    tryToStartedCount++;
                }
            }
            else if (allInRangeCount < 13 && isStarted == 0)
            {
                if (tryToStartedCount <= 0)
                {
                    tryToStartedCount = 0;
                }
                else
                {
                    tryToStartedCount -= 1;
                }
            }
            else if (allInRangeCount < 13 && isStarted == 1)
            {
                tryToStopCount += m_DECREASERATE;
            }

            //进入计时状态
            if (tryToStartedCount >= m_STARTCOUNTMAX && isStarted == 0)
            {
                isStarted = 1;
                tryToStopCount = 0;
                //tryToStartedCount = 0;
                //保存计时状态的角度
                for (int i = 0; i < 13; i++)
                {
                    startedAngle[i] = angle[i];
                }
                startList.Add(lineIndex);
                stableAngleList.Add(angle);
                doudongListSum.Clear();


                m_standard = (float)ran.Next(700, 950) / 10.0F;
                m_incline = 100 - Math.Abs(reqMainAngleRelative(fArray[4 * 0 + 3], fArray[4 * 0 + 0], fArray[4 * 0 + 1], fArray[4 * 0 + 2], 1, 1, 0, 0, 0, 2) - 90) * 2.0F;
                if (m_incline < 0)
                {
                    m_incline = 0;
                }
                if (m_index != TestMathodName.CoreFunctionalTest && m_index != TestMathodName.CoreFunctionalTestOpposite)
                {
                    m_balance = 100 - Math.Abs(reqMainAngleRelative(fArray[4 * 1 + 3], fArray[4 * 1 + 0], fArray[4 * 1 + 1], fArray[4 * 1 + 2], 2, 1, 0, 0, 0, 2) -
                                               reqMainAngleRelative(fArray[4 * 2 + 3], fArray[4 * 2 + 0], fArray[4 * 2 + 1], fArray[4 * 2 + 2], 2, 1, 0, 0, 0, 2)) * 3.0F
                                    - Math.Abs(reqMainAngleRelative(fArray[4 * 3 + 3], fArray[4 * 3 + 0], fArray[4 * 3 + 1], fArray[4 * 3 + 2], 2, 1, 0, 0, 0, 2) -
                                               reqMainAngleRelative(fArray[4 * 4 + 3], fArray[4 * 4 + 0], fArray[4 * 4 + 1], fArray[4 * 4 + 2], 2, 1, 0, 0, 0, 2)) * 3.0F;
                    if (m_balance < 0)
                    {
                        m_balance = 0;
                    }
                }
                else
                {
                    m_balance = (float)ran.Next(700, 999) / 10.0F; ;
                }

            }
            else
            {
                //此处退出计时状态
            }

            //每180秒更新一次状态计时
            if (isStarted == 1 && allInRangeCount >= 13 && tryToStartedCount >= m_STARTCOUNTMAX && m_index == TestMathodName.PlankTest)
            {
                if ((lineIndex - startList[startList.Count() - 1]) % 18000 == 0)
                {
                    //更新计时状态的角度
                    for (int i = 0; i < 13; i++)
                    {
                        startedAngle[i] = angle[i];
                    }
                }
            }

            //飞燕式只保留最高值
            if (isStarted == 1 && allInRangeCount >= 13 && tryToStartedCount >= m_STARTCOUNTMAX && m_index == TestMathodName.FeiYanShi)
            {
                if (lineIndex % 20 == 0)
                {
                    for (int i = 1; i <= 4; i++)
                    {
                        float delta = angle[i] - startedAngle[i];
                        if (delta > 0 && delta <= 1.0F)
                        {
                            startedAngle[i] += delta;
                        }
                        else if (delta >= 1.0F)
                        {
                            startedAngle[i] += 1.0F;
                        }
                    }
                }
            }

            //开始判断衰退
            int allOutOfRangeCount = 0;
            for (int i = 0; i < 13; i++)
            {
                if (angle[i] > startedAngle[i] + deltaRangeUp[i] || angle[i] < startedAngle[i] + deltaRangeDown[i])
                {
                    allOutOfRangeCount++;
                    m_angleAndJointDetectUnstableFlag[i] = 0;
                }
                else
                {
                    m_angleAndJointDetectUnstableFlag[i] = 1;
                }
            }
            if (allOutOfRangeCount > 0 && isStarted == 1)
            {
                tryToStopCount += m_DECREASERATE;
            }
            else if (allOutOfRangeCount == 0 && isStarted == 1)
            {
                tryToStopCount = 0;
            }

            //此处退出计时状态
            if (tryToStopCount >= m_STOPCOUNTMAX)
            {
                isStarted = 0;
                tryToStopCount = 0;
                tryToStartedCount = 0;
                //取消保存计时状态的角度
                for (int i = 0; i < 13; i++)
                {
                    startedAngle[i] = 0;
                }
                endList.Add(lineIndex);
                float doudongSum = 0;
                for (int ii = 0; ii < doudongListSum.Count(); ii++)
                {
                    doudongSum += doudongListSum[ii];
                }
                if (doudongListSum.Count() > 0)
                {
                    doudongList.Add(doudongSum / (float)doudongListSum.Count());
                }
                else
                {
                    doudongList.Add(0);
                }
            }

            //if(lineIndex < 7000)
            //{
            //    string msg = lineIndex.ToString() + " " + isStarted + " " + tryToStopCount + " " + tryToStartedCount + " " + m_jishiFlag + " " + m_jindutiao + " " + m_maxDuration + " " + m_timeCount;
            //    Console.WriteLine(msg);
            //}

        }

        void calSingleLegSquat(float[] fArray, ref int isStarted, ref int tryToStartedCount, ref int tryToStopCount, 
                               ref float squatMaxAngle, int isLeftOrRightXiGaiSquatNum, int isLeftOrRightXiGaiStraightNum, int lineIndex, 
                               ref List<float> startList, ref List<float> endList, ref List<float[]> stableAngleList, ref List<float> doudongList, ref List<float> doudongListSum,
                               ref int tryToStableValueCount)
        {
            //参数计算
            //range = 腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节

            float[] angle = new float[13];
            int index = 0;
            angle[0] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 1;
            angle[1] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 2;
            angle[2] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 3;
            angle[3] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 4;
            angle[4] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 5;
            angle[5] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);
            index = 6;
            angle[6] = reqMainAngleRelative(fArray[4 * index + 3], fArray[4 * index + 0], fArray[4 * index + 1], fArray[4 * index + 2], 2, 1, 0, 0, 0, 2);

            int index1 = 0, index2 = 1;
            angle[7] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 0; index2 = 2;
            angle[8] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 1; index2 = 3;
            angle[9] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 2; index2 = 4;
            angle[10] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 3; index2 = 5;
            angle[11] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);
            index1 = 4; index2 = 6;
            angle[12] = reqMainAngleRelative(fArray[4 * index1 + 3], fArray[4 * index1 + 0], fArray[4 * index1 + 1], fArray[4 * index1 + 2], 2,
                                                    fArray[4 * index2 + 3], fArray[4 * index2 + 0], fArray[4 * index2 + 1], fArray[4 * index2 + 2], 2);

            //显示错误信息
            if (m_index == TestMathodName.BalanceTestDynamic1Left || m_index == TestMathodName.BalanceTestDynamic1Right)
            {
                if (lineIndex % (100 * g_SamplingRate) == 0)
                {
                    m_errors.Clear();
                    if (angle[isLeftOrRightXiGaiStraightNum] > 20)
                    {
                        Dictionary<string, float> err1 = new Dictionary<string, float>();
                        err1.Add("Part", isLeftOrRightXiGaiStraightNum);  //  膝盖关节
                        err1.Add("Level", angle[isLeftOrRightXiGaiStraightNum] - 20);
                        err1.Add("Detail", 0); // 打弯
                        m_errors.Add(err1);
                    }
                }
            }

            //检测开始
            Random ran = new Random();
            if (isStarted == 0)
            {
                if(angle[isLeftOrRightXiGaiSquatNum] > 25 && angle[isLeftOrRightXiGaiStraightNum] < 20 && angle[isLeftOrRightXiGaiStraightNum-6] > 30)
                {
                    tryToStartedCount++;
                }

                if(tryToStartedCount >= m_STARTCOUNTMAX)
                {
                    isStarted = 1;
                    tryToStartedCount = m_STARTCOUNTMAX;
                    tryToStopCount = 0;
                    tryToStableValueCount = 0;
                    startList.Add(lineIndex);
                    //stableAngleList.Add(angle[isLeftOrRightXiGaiSquatNum]);
                    doudongListSum.Clear();

                    m_standard = (float)ran.Next(700, 950) / 10.0F;
                    m_incline = 100 - Math.Abs(reqMainAngleRelative(fArray[4 * 0 + 3], fArray[4 * 0 + 0], fArray[4 * 0 + 1], fArray[4 * 0 + 2], 1, 1, 0, 0, 0, 2) - 90) * 2.0F;
                    if (m_incline < 0)
                    {
                        m_incline = 0;
                    }
                    if (m_index != TestMathodName.CoreFunctionalTest && m_index != TestMathodName.CoreFunctionalTestOpposite)
                    {
                        m_balance = 100 - Math.Abs(reqMainAngleRelative(fArray[4 * 1 + 3], fArray[4 * 1 + 0], fArray[4 * 1 + 1], fArray[4 * 1 + 2], 2, 1, 0, 0, 0, 2) -
                                                   reqMainAngleRelative(fArray[4 * 2 + 3], fArray[4 * 2 + 0], fArray[4 * 2 + 1], fArray[4 * 2 + 2], 2, 1, 0, 0, 0, 2)) * 3.0F
                                        - Math.Abs(reqMainAngleRelative(fArray[4 * 3 + 3], fArray[4 * 3 + 0], fArray[4 * 3 + 1], fArray[4 * 3 + 2], 2, 1, 0, 0, 0, 2) -
                                                   reqMainAngleRelative(fArray[4 * 4 + 3], fArray[4 * 4 + 0], fArray[4 * 4 + 1], fArray[4 * 4 + 2], 2, 1, 0, 0, 0, 2)) * 3.0F;
                        if (m_balance < 0)
                        {
                            m_balance = 0;
                        }
                    }
                    else
                    {
                        m_balance = (float)ran.Next(700, 999) / 10.0F; ;
                    }
                }
            }

            //检测最大角度
            if(isStarted == 1)
            {
                if(angle[isLeftOrRightXiGaiSquatNum] > 25 && angle[isLeftOrRightXiGaiStraightNum] < 20 && angle[isLeftOrRightXiGaiStraightNum - 6] > 30)
                {
                    if(squatMaxAngle < angle[isLeftOrRightXiGaiSquatNum])
                    {
                        tryToStableValueCount++;
                        if(tryToStableValueCount == 100 * g_SamplingRate)
                        {
                            squatMaxAngle = angle[isLeftOrRightXiGaiSquatNum] + 3;
                            if (m_maxDuration < squatMaxAngle)
                            {
                                m_maxDuration = squatMaxAngle;
                            }
                            //tryToStableValueCount = 0;
                        }
                        if(tryToStableValueCount >= 130)
                        {
                            tryToStableValueCount = 0;
                        }
                        
                    }
                    else if (squatMaxAngle >= angle[isLeftOrRightXiGaiSquatNum])
                    {
                        if (tryToStableValueCount > 0 && tryToStableValueCount < 100)
                        {
                            tryToStableValueCount--;
                        }else if(tryToStableValueCount > 100)
                        {
                            //tryToStableValueCount--;
                        }
                    }
                }
                else
                {
                    tryToStableValueCount = 0;
                }
            }

            //检测结束
            if (isStarted == 1)
            {
                if(angle[isLeftOrRightXiGaiSquatNum] < 20)
                {
                    tryToStopCount++;
                    tryToStableValueCount = 0;
                }

                if(tryToStopCount >= m_STOPCOUNTMAX)
                {
                    isStarted = 0;
                    tryToStartedCount = 0;
                    tryToStopCount = 0;
                    
                    
                    squatMaxAngle = 0;

                    endList.Add(lineIndex);
                    float doudongSum = 0;
                    for (int ii = 0; ii < doudongListSum.Count(); ii++)
                    {
                        doudongSum += doudongListSum[ii];
                    }
                    if (doudongListSum.Count() > 0)
                    {
                        doudongList.Add(doudongSum / (float)doudongListSum.Count());
                    }
                    else
                    {
                        doudongList.Add(0);
                    }
                }
            }

            //if (lineIndex % (10 * g_SamplingRate) == 0)
            //{
            //    string msg = " m_maxDuration:" + m_maxDuration + " squatMaxAngle: " + squatMaxAngle + " tryToStopCount: " + tryToStopCount
            //                    + " tryToStartedCount: " + tryToStartedCount + " isStarted: " + isStarted + " m_jindutiao:" + m_jindutiao + " tryToStableValueCount: " + tryToStableValueCount + "\n";
            //    Console.WriteLine(msg);
            //}

        }

        public void calculationSingleTime(float[] floatArray, int lineIndex)
        {
            float[] w = new float[7], x = new float[7], y = new float[7], z = new float[7], accx = new float[7], accy = new float[7], accz = new float[7], gyrox = new float[7], gyroy = new float[7], gyroz = new float[7];
            for (int i = 0; i < 7; i++)
            {
                x[i] = floatArray[4 * i + 0];
                y[i] = floatArray[4 * i + 1];
                z[i] = floatArray[4 * i + 2];
                w[i] = floatArray[4 * i + 3];
                accx[i] = floatArray[3 * i + 28 + 0];
                accy[i] = floatArray[3 * i + 28 + 1];
                accz[i] = floatArray[3 * i + 28 + 2];
                gyrox[i] = floatArray[3 * i + 49 + 0];
                gyroy[i] = floatArray[3 * i + 49 + 1];
                gyroz[i] = floatArray[3 * i + 49 + 2];
            }

            //range = 腰部，左大腿，右大腿，左小腿，右小腿，左脚，右脚，左髋关节，右髋关节，左膝关节，右膝关节，左踝关节，右踝关节
            //float[] rangeUp = new float[] {110, 110, 110, 110, 110, 180, 180, 30, 30, 20, 20, 180, 180};
            //float[] rangeDown = new float[] { 70, 70, 70, 70, 70, 0, 0, 0, 0, 0, 0, 0, 0 };
            //float[] deltaRangeUp = new float[] { 5, 5, 5, 5, 5, 15, 15, 5, 5, 5, 5, 15, 15 };
            //float[] deltaRangeDown = new float[] { -5, -5, -5, -5, -5, -15, -15, -10, -10, -10, -10, -15, -15 };
            
            if(m_index == TestMathodName.BalanceTestDynamic1Left || m_index == TestMathodName.BalanceTestDynamic1Right)
            {
                //静态平衡1 - 单腿深蹲
                if(m_index == TestMathodName.BalanceTestDynamic1Left)
                {
                    calSingleLegSquat(floatArray, ref hermesNewBalanceTest.isStarted, ref hermesNewBalanceTest.tryToStartedCount, ref hermesNewBalanceTest.tryToStopCount,
                    ref hermesNewBalanceTest.squatMaxAngle, 9, 10, lineIndex, ref hermesNewBalanceTest.startList, ref hermesNewBalanceTest.endList, ref hermesNewBalanceTest.stableAngleList,
                                        ref hermesNewBalanceTest.doudongList, ref hermesNewBalanceTest.doudongListSum, ref hermesNewBalanceTest.tryToStableValueCount);
                }
                else if(m_index == TestMathodName.BalanceTestDynamic1Right)
                {
                    calSingleLegSquat(floatArray, ref hermesNewBalanceTest.isStarted, ref hermesNewBalanceTest.tryToStartedCount, ref hermesNewBalanceTest.tryToStopCount,
                    ref hermesNewBalanceTest.squatMaxAngle, 10, 9, lineIndex, ref hermesNewBalanceTest.startList, ref hermesNewBalanceTest.endList, ref hermesNewBalanceTest.stableAngleList,
                                        ref hermesNewBalanceTest.doudongList, ref hermesNewBalanceTest.doudongListSum,ref hermesNewBalanceTest.tryToStableValueCount);
                }
                
            }
            else
            {
                calSinglePartCalculationEx(floatArray, rangeUp, rangeDown, ref hermesNewBalanceTest.isStarted, ref hermesNewBalanceTest.tryToStartedCount,
                                        ref hermesNewBalanceTest.startedAngle, ref hermesNewBalanceTest.tryToStopCount,
                                        deltaRangeUp, deltaRangeDown, ref hermesNewBalanceTest.startList, ref hermesNewBalanceTest.endList, ref hermesNewBalanceTest.stableAngleList,
                                        ref hermesNewBalanceTest.doudongList, ref hermesNewBalanceTest.doudongListSum, lineIndex);
            }

            m_jishiFlag = hermesNewBalanceTest.isStarted;
            if (hermesNewBalanceTest.isStarted == 1)
            {
                m_timeCount = (int)((lineIndex - (int)hermesNewBalanceTest.startList[hermesNewBalanceTest.startList.Count() - 1]) * ((float)10 / (float)g_SamplingRate));
                float zuodatuiDoudong = floatArray[3 * 1 + 49 + 0] * floatArray[3 * 1 + 49 + 0] + floatArray[3 * 1 + 49 + 1] * floatArray[3 * 1 + 49 + 1] + floatArray[3 * 1 + 49 + 2] * floatArray[3 * 1 + 49 + 2];
                float youdatuiDoudong = floatArray[3 * 2 + 49 + 0] * floatArray[3 * 2 + 49 + 0] + floatArray[3 * 2 + 49 + 1] * floatArray[3 * 2 + 49 + 1] + floatArray[3 * 2 + 49 + 2] * floatArray[3 * 2 + 49 + 2];
                float doudong = ((float)Math.Sqrt(zuodatuiDoudong) + (float)Math.Sqrt(youdatuiDoudong)) / 2.0F;
                hermesNewBalanceTest.doudongListSum.Add(doudong);
            }
            else
            {
                m_timeCount = 0;
            }
            if (m_JINDUTIAO != 0)
            {
                if ((float)m_timeCount / 10.0F / (float)m_JINDUTIAO * (float)g_SamplingRate > 1)
                {
                    m_jindutiao = 1;
                }
                else
                {
                    m_jindutiao = (float)m_timeCount / 10.0F / (float)m_JINDUTIAO * (float)g_SamplingRate;
                }

            }
            else
            {
                if (hermesNewBalanceTest.isStarted == 0 && m_index != TestMathodName.BalanceTestDynamic1Right && m_index != TestMathodName.BalanceTestDynamic1Left)
                {
                    m_jindutiao = (float)hermesNewBalanceTest.tryToStartedCount / (float)m_STARTCOUNTMAX;
                }
                else if (hermesNewBalanceTest.isStarted == 1 && m_index != TestMathodName.BalanceTestDynamic1Right && m_index != TestMathodName.BalanceTestDynamic1Left)
                {
                    m_jindutiao = 1 - (float)hermesNewBalanceTest.tryToStopCount / (float)m_STOPCOUNTMAX;
                }
                else if (hermesNewBalanceTest.isStarted == 0 && (m_index == TestMathodName.BalanceTestDynamic1Right || m_index == TestMathodName.BalanceTestDynamic1Left))
                {
                    m_jindutiao = ((float)hermesNewBalanceTest.tryToStartedCount + (float)hermesNewBalanceTest.tryToStableValueCount) / ((float)m_STARTCOUNTMAX + (float)100.0F* (float)g_SamplingRate);
                }
                else if (hermesNewBalanceTest.isStarted == 1 && (m_index == TestMathodName.BalanceTestDynamic1Right || m_index == TestMathodName.BalanceTestDynamic1Left) && hermesNewBalanceTest.tryToStopCount == 0)
                {
                    m_jindutiao = 0.125F - (float)hermesNewBalanceTest.tryToStopCount / (float)m_STOPCOUNTMAX/8.0F + (float)hermesNewBalanceTest.tryToStableValueCount / ((float)100.0F * (float)g_SamplingRate)*0.875F;
                }
                else if (hermesNewBalanceTest.isStarted == 1 && (m_index == TestMathodName.BalanceTestDynamic1Right || m_index == TestMathodName.BalanceTestDynamic1Left) && hermesNewBalanceTest.tryToStopCount > 0)
                {
                    m_jindutiao = 1 - (float)hermesNewBalanceTest.tryToStopCount / (float)m_STOPCOUNTMAX;
                }

            }
            //if (m_timeCount <= 6200 && m_timeCount >= 6000 && hermesNewBalanceTest.isStarted == 1 && m_index == TestMathodName.PilatesTrunkFlexion)
            //{
            //    float[] tmp = hermesNewBalanceTest.stableAngleList[hermesNewBalanceTest.stableAngleList.Count() - 1];
            //    if (m_maxDuration < (tmp[7] + tmp[8]) / 2.0F)
            //    {
            //        m_maxDuration = (tmp[7] + tmp[8]) / 2.0F * 100.0F;
            //    }
            //}


            //Console.WriteLine("calculationSingleTime输出！");

            ////QListIterator<float> recordstartIteratorNew(*recordStartNew);
            //IEnumerator<float> recordstartIteratorNew = hermesTmp.recordStartNew.GetEnumerator();
            //////QListIterator<float> recordstopIteratorNew(*recordStopNew);
            //IEnumerator<float> recordstopIteratorNew = hermesTmp.recordStopNew.GetEnumerator();
            //////QListIterator<float> recordaverageIteratorNew(*recordAverageNew);
            //IEnumerator<float> recordaverageIteratorNew = hermesTmp.recordAverageNew.GetEnumerator();
            //while (recordaverageIteratorNew.MoveNext() && recordstopIteratorNew.MoveNext() && recordstartIteratorNew.MoveNext())
            //{
            //    float a = recordaverageIteratorNew.Current;
            //    float start = recordstartIteratorNew.Current;
            //    float stop = recordstopIteratorNew.Current;
            //    //qDebug("average: %f Start time: %f Stop time: %f Duration: %f", a, start, stop, stop - start);
            //    string msg = "lineIndex:" + lineIndex + "average" + ":" + a.ToString() + " Start time:" + start.ToString() + " Stop time:" + stop.ToString() + " Duration:" + (stop - start).ToString();
            //    Console.WriteLine(msg);
            //}
        }

        public int calResult(int lineIndex)
        {
            //200个点

            float[] floatArrayTmp = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];

            for (int iii = 0; iii < 7; iii++)
            {
                floatArrayTmp[4 * iii + 1] = 0F;
                floatArrayTmp[4 * iii + 2] = 1F;
                floatArrayTmp[4 * iii + 3] = 0F;
                floatArrayTmp[4 * iii + 0] = 0F;

                if (iii == 0)
                {
                    floatArrayTmp[4 * iii + 1] = 0.907F;
                    floatArrayTmp[4 * iii + 3] = (float)Math.Sqrt(1 - floatArrayTmp[4 * iii + 1] * floatArrayTmp[4 * iii + 1]);
                }

                if (iii == 3 || iii == 4)
                {
                    floatArrayTmp[4 * iii + 1] = 0.707F;
                }


                if (iii == 3 || iii == 4)
                {
                    floatArrayTmp[4 * iii + 3] = (float)Math.Sqrt(1 - floatArrayTmp[4 * iii + 1] * floatArrayTmp[4 * iii + 1]);
                }
                floatArrayTmp[3 * iii + 0 + 28] = 900;
                floatArrayTmp[3 * iii + 1 + 28] = 900;
                floatArrayTmp[3 * iii + 2 + 28] = 900;
                floatArrayTmp[3 * iii + 0 + 49] = 900;
                floatArrayTmp[3 * iii + 1 + 49] = 900;
                floatArrayTmp[3 * iii + 2 + 49] = 900;
            }


            for (int iiii = 0; iiii < 550; iiii++)
            {
                floatArrayTmp[4 * 7 + 3 * 7 + 3 * 7] = lineIndex + iiii;
                calculationSingleTime(floatArrayTmp, lineIndex + 10 + iiii);
            }

            startList.Clear();
            endList.Clear();


            totalStartList.Clear();
            totalEndList.Clear();

            float maxDuration = 0;
            IEnumerator<float> totalStartIterator = totalStartList.GetEnumerator();
            //QListIterator<float> subEndIterator(*subEndList);
            IEnumerator<float> totalEndIterator = totalEndList.GetEnumerator();
            while (totalStartIterator.MoveNext() && totalEndIterator.MoveNext())
            {
                float start = totalStartIterator.Current;
                float end = totalEndIterator.Current;
                if (maxDuration < (end - start))
                {
                    maxDuration = (end - start);
                }
            }

            float maxDurationEx = 0;
            if (hermesNewBalanceTest.startList.Count() == hermesNewBalanceTest.endList.Count() && hermesNewBalanceTest.startList.Count() == hermesNewBalanceTest.doudongList.Count())
            {
                for (int i = 0; i < hermesNewBalanceTest.startList.Count(); i++)
                {
                    if (maxDurationEx < hermesNewBalanceTest.endList[i] - hermesNewBalanceTest.startList[i])
                    {
                        maxDurationEx = hermesNewBalanceTest.endList[i] - hermesNewBalanceTest.startList[i];
                        if (m_index == TestMathodName.V_Sit)
                        {
                            m_shaking = 100.0F - hermesNewBalanceTest.doudongList[i] * 2.0F;
                        }
                        else if (m_index == TestMathodName.CoreFunctionalTest)
                        {
                            m_shaking = 100.0F - hermesNewBalanceTest.doudongList[i] * 0.3F;
                        }
                        else if (m_index == TestMathodName.CoreFunctionalTestOpposite)
                        {
                            m_shaking = 100.0F - hermesNewBalanceTest.doudongList[i] * 0.3F;
                        }
                        else
                        {
                            m_shaking = 100.0F - hermesNewBalanceTest.doudongList[i] * 1.0F;
                        }
                        if (m_shaking <= 13)
                        {
                            Random ran = new Random();
                            m_shaking = (float)ran.Next(130, 150) / 10.0F;
                        }
                        else if (m_shaking > 100)
                        {
                            m_shaking = 100;
                        }
                        else if (m_shaking == float.NaN)
                        {
                            Random ran = new Random();
                            m_shaking = (float)ran.Next(130, 150) / 10.0F;
                        }
                    }
                }
            }

            if (m_maxDuration < maxDurationEx && m_index != TestMathodName.BalanceTestDynamic1Right && m_index != TestMathodName.BalanceTestDynamic1Left)
            {
                m_maxDuration = maxDurationEx / 100.0F / (float)g_SamplingRate; ;
            }

            //if (m_index == TestMathodName.PilatesTrunkFlexion)
            //{

            //}
            //else
            //{
            //    if (m_maxDuration < maxDurationEx)
            //    {
            //        m_maxDuration = maxDurationEx;
            //    }
            //}
            return 0;
        }
    } //平衡性测试，主要类

    public class NewRomBase //新版关节灵活度测试基类，不要实例化
    {
        public const float PI = 3.14159265358979323846F;

        public struct vector3d
        {
            public double x;
            public double y;
            public double z;
            public vector3d(float x_, float y_, float z_)
            {
                x = x_;
                y = y_;
                z = z_;
            }
        };//欧拉角结构体

        public struct Vector333fff

        {
            public float i;
            public float j;
            public float k;
            public Vector333fff(float x_, float y_, float z_)
            {
                i = x_;
                j = y_;
                k = z_;
            }
        };

        public struct Quat_t
        {
            public double w, x, y, z;
            public Quat_t(float w_, float x_, float y_, float z_)
            {
                w = w_;
                x = x_;
                y = y_;
                z = z_;
            }
        };//四元素结构体

        //四元素旋转
        //quat1:输入原始四元素
        //quat2:输入旋转向量四元素
        //返回：输出旋转后的四元素
        public int quat_pro(Quat_t quat1, Quat_t quat2, out Quat_t quat3)
        {
            quat3 = new Quat_t();
            double w1, x1, y1, z1;
            double w2, x2, y2, z2;
            w2 = quat1.w;
            x2 = quat1.x;
            y2 = quat1.y;
            z2 = quat1.z;

            w1 = quat2.w;
            x1 = quat2.x;
            y1 = quat2.y;
            z1 = quat2.z;

            quat3.w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
            quat3.x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
            quat3.y = w1 * y2 - x1 * z2 + y1 * w2 + z1 * x2;
            quat3.z = w1 * z2 + x1 * y2 - y1 * x2 + z1 * w2;
            return 0;
        }

        public float reqMainAnglejiao(float w, float x, float y, float z)
        {
            float Angle = 2 * x * z - 2 * w * y;
            Angle = 90F - (float)Math.Acos(Angle) / PI * 180F;
            //qDebug() << Angle;
            return Angle;
        }

        public float reqMainAngle(float w, float x, float y, float z)
        {
            float Angle = 1 - 2 * x * x - 2 * y * y;
            Angle = (float)Math.Acos(Angle) / PI * 180F;
            return Angle;
        }

        public void reqRotationQuat(Quat_t q1, Quat_t q2, out Quat_t qOut)
        {
            //X1.adjoint()*X2
            qOut = new Quat_t();
            //qDebug() << "test1 " << qOut->w << qOut->x << qOut->y << qOut->z;
            float w1 = (float)q1.w; float x1 = (float)q1.x; float y1 = (float)q1.y; float z1 = (float)q1.z;
            float w2 = (float)q2.w; float x2 = (float)q2.x; float y2 = (float)q2.y; float z2 = (float)q2.z;
            Quat_t quat1 = new Quat_t(w1, x1, y1, z1);//rool方向上旋转90度
            double quat_total1 = Math.Sqrt((quat1.x) * (quat1.x) + (quat1.y) * (quat1.y) + (quat1.z) * (quat1.z) + (quat1.w) * (quat1.w));
            quat1.x = -quat1.x / quat_total1; quat1.y = -quat1.y / quat_total1; quat1.z = -quat1.z / quat_total1; quat1.w = quat1.w / quat_total1;
            Quat_t quat2 = new Quat_t(w2, x2, y2, z2);
            double quat_total2 = Math.Sqrt((quat2.x) * (quat2.x) + (quat2.y) * (quat2.y) + (quat2.z) * (quat2.z) + (quat2.w) * (quat2.w));
            quat2.x = quat2.x / quat_total2; quat2.y = quat2.y / quat_total2; quat2.z = quat2.z / quat_total2; quat2.w = quat2.w / quat_total2;
            //Quat_t qOut_t = { 0,0,0,0 };
            quat_pro(quat2, quat1, out qOut);
            //qDebug() << "test2 " << qOut->w << qOut->x << qOut->y << qOut->z;
        }

        public float reqPianAnglejiao(Quat_t q)
        {
            float xx = (float)q.x; float yy = (float)q.y; float zz = (float)q.z; float ww = (float)q.w;
            Vector333fff c = new Vector333fff(0, 0, 1);
            float www = ww / (float)Math.Sqrt(ww * ww + yy * yy);
            float yyy = yy / (float)Math.Sqrt(ww * ww + yy * yy);
            Vector333fff a = new Vector333fff(1 - 2 * yyy * yyy, 0, -2 * www * yyy);
            Vector333fff m = new Vector333fff(0, 0, 0);
            Vector333fff n = new Vector333fff(0, 0, 0);
            m.i = c.j * a.k - a.j * c.k; m.j = c.k * a.i - a.k * c.i; m.k = c.i * a.j - a.i * c.j; // u1v2-v1u2 , u2v0-v2u0 , u0v1-u1v0

            Vector333fff b = new Vector333fff(1 - 2 * zz * zz - 2 * yy * yy, 2 * xx * yy + 2 * ww * zz, 2 * xx * zz - 2 * ww * yy);
            n.i = c.j * b.k - b.j * c.k; n.j = c.k * b.i - b.k * c.i; n.k = c.i * b.j - b.i * c.j; // u1v2-v1u2 , u2v0-v2u0 , u0v1-u1v0
            float mnorm = (float)Math.Sqrt(m.i * m.i + m.j * m.j + m.k * m.k);
            float nnorm = (float)Math.Sqrt(n.i * n.i + n.j * n.j + n.k * n.k);
            float mdotn = m.i * n.i + m.j * n.j + m.k * n.k;
            float angle_pian = (float)Math.Acos(mdotn / nnorm / mnorm) / PI * 180;
            return angle_pian;
        }

        public float reqPianAngle(Quat_t q)
        {
            float xx = (float)q.x; float yy = (float)q.y; float zz = (float)q.z; float ww = (float)q.w;
            Vector333fff c = new Vector333fff(0, 0, 1);
            float www = ww / (float)Math.Sqrt(ww * ww + yy * yy);
            float yyy = yy / (float)Math.Sqrt(ww * ww + yy * yy);
            Vector333fff a = new Vector333fff(-2 * www * yyy, 0, 1 - 2 * yyy * yyy);
            Vector333fff m = new Vector333fff(0, 0, 0);
            Vector333fff n = new Vector333fff(0, 0, 0);
            m.i = c.j * a.k - a.j * c.k; m.j = c.k * a.i - a.k * c.i; m.k = c.i * a.j - a.i * c.j; // u1v2-v1u2 , u2v0-v2u0 , u0v1-u1v0

            Vector333fff b = new Vector333fff(2 * xx * zz - 2 * ww * yy, 2 * yy * zz + 2 * ww * xx, 1 - 2 * xx * xx - 2 * yy * yy);
            n.i = c.j * b.k - b.j * c.k; n.j = c.k * b.i - b.k * c.i; n.k = c.i * b.j - b.i * c.j; // u1v2-v1u2 , u2v0-v2u0 , u0v1-u1v0
            float mnorm = (float)Math.Sqrt(m.i * m.i + m.j * m.j + m.k * m.k);
            float nnorm = (float)Math.Sqrt(n.i * n.i + n.j * n.j + n.k * n.k);
            float mdotn = m.i * n.i + m.j * n.j + m.k * n.k;
            float angle_pian = (float)Math.Acos(mdotn / nnorm / mnorm) / PI * 180;
            return angle_pian;
        }


        public float reqMainAngleRelativeSinXZ(
                                        float w0, float x0, float y0, float z0,
                                        float w, float x, float y, float z)
        {

            float l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
            float m = 2 * x0 * y0 + 2 * w0 * z0;
            float n = 2 * x0 * z0 - 2 * w0 * y0;
            float o = 2 * x * z + 2 * w * y;
            float p = 2 * y * z - 2 * w * x;
            float q = 1 - 2 * x * x - 2 * y * y;

            //    float Angle = sqrt((m*q - n * p)*(m*q - n * p) + (n*o - l * q)*(n*o - l * q) + (l*p - m * o)*(l*p - m * o));
            //    Angle = asin(Angle) / PI * 180;
            //float Angle = acos(l * o + m * p + n * q) / PI * 180;
            //return Angle;

            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        public float reqMainAngleRelative(float w0, float x0, float y0, float z0, int direction0,
                                   float w, float x, float y, float z, int direction)
        {
            float l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            switch (direction)
            {
                case 0:      //X方向
                    o = 1 - 2 * y * y - 2 * z * z;
                    p = 2 * x * y + 2 * w * z;
                    q = 2 * x * z - 2 * w * y;
                    break;
                case 1:      //Y方向
                    o = 2 * x * y - 2 * w * z;
                    p = 1 - 2 * x * x - 2 * z * z;
                    q = 2 * y * z + 2 * w * x;
                    break;
                case 2:      //Z方向
                    o = 2 * x * z + 2 * w * y;
                    p = 2 * y * z - 2 * w * x;
                    q = 1 - 2 * x * x - 2 * y * y;
                    break;
                default:
                    break;
            }
            //    float Angle = sqrt((m*q - n * p)*(m*q - n * p) + (n*o - l * q)*(n*o - l * q) + (l*p - m * o)*(l*p - m * o));
            //    Angle = asin(Angle) / PI * 180;
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        public float reqMainAngleRelativeEXFirst(float l, float m, float n,
                                          float w, float x, float y, float z, int direction)
        {
            float o = 0, p = 0, q = 0;
            switch (direction)
            {
                case 0:      //X方向
                    o = 1 - 2 * y * y - 2 * z * z;
                    p = 2 * x * y + 2 * w * z;
                    q = 2 * x * z - 2 * w * y;
                    break;
                case 1:      //Y方向
                    o = 2 * x * y - 2 * w * z;
                    p = 1 - 2 * x * x - 2 * z * z;
                    q = 2 * y * z + 2 * w * x;
                    break;
                case 2:      //Z方向
                    o = 2 * x * z + 2 * w * y;
                    p = 2 * y * z - 2 * w * x;
                    q = 1 - 2 * x * x - 2 * y * y;
                    break;
                default:
                    break;
            }
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        public float reqMainAngleRelativeEXSecond(float w0, float x0, float y0, float z0, int direction0,
                                           float o, float p, float q)
        {
            float l = 0, m = 0, n = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        public float reqMainAngleRelativeEXBoth(float l, float m, float n,
                                         float o, float p, float q)
        {
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }

        public void reqCrossProduct(float w0, float x0, float y0, float z0, int direction0,
                             float w, float x, float y, float z, int direction,
                             out float[] output)
        {
            output = new float[3];
            float l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            switch (direction)
            {
                case 0:      //X方向
                    o = 1 - 2 * y * y - 2 * z * z;
                    p = 2 * x * y + 2 * w * z;
                    q = 2 * x * z - 2 * w * y;
                    break;
                case 1:      //Y方向
                    o = 2 * x * y - 2 * w * z;
                    p = 1 - 2 * x * x - 2 * z * z;
                    q = 2 * y * z + 2 * w * x;
                    break;
                case 2:      //Z方向
                    o = 2 * x * z + 2 * w * y;
                    p = 2 * y * z - 2 * w * x;
                    q = 1 - 2 * x * x - 2 * y * y;
                    break;
                default:
                    break;
            }
            float mo0 = (float)Math.Sqrt(l * l + m * m + n * n);
            float mo = (float)Math.Sqrt(o * o + p * p + q * q);
            float i = (m * q - n * p) / mo0 / mo; float j = (n * o - l * q) / mo0 / mo; float k = (l * p - m * o) / mo0 / mo;
            float total = (float)Math.Sqrt(i * i + j * j + k * k);
            output[0] = i / total;
            output[1] = j / total;
            output[2] = k / total;
        }
    }

    public class HermesROMTest : NewRomBase 
    {
        public float _initFlag = -1;
        public float _angle_zhunzhi_l = -1, _angle_zhunzhi_r = -1;
        public float _angle_zhun_count_l = -1, _angle_zhun_count_r = -1;
        public float _angle_zhun_max_l = -1, _angle_zhun_max_r = -1;
        public float _angleOutput_l, _angleOutput_r;
        public float _rateOfProcess_l, _rateOfProcess_r;
        public float _angle_pian_l, _angle_pian_r;
        public int bodyIndex1;
        public int bodyIndex2;
        public float[] range = new float[2];
        public float[] wrongRange = new float[40];
        float[] wrongNumber = new float[30];
        //最大持续时间（单位10毫秒）
        public float m_maxDuration_left;
        public float m_maxDuration_right;
        //计时进度条(0-1)
        public float m_jindutiao_left;
        public float m_jindutiao_right;
        //那条腿(0=左腿；1=右腿；-1=未统计成功)
        public float m_whichone_left;
        public float m_whichone_right;
        //m_anglePian
        public float m_anglePian_left;
        public float m_anglePian_right;

        public const int rateOfProcessTotal = 200;
        public const int delayCount = 200;
        public const int deltaAngle = 3;

        public TestMathodName m_index;

        public enum TestMathodName
        {
            zhixiqukuan = 0,
            zhixiqukuanFuzhu = 1,
            housheng = 2,
            houshengFuzhu = 3,
            kuanwaizhan = 4,
            kuanneishou = 5,
            kuanwaixuan = 6,
            kuanneixuan = 7,
            quxi = 8,
            zubeiqu = 9,
            zuzhiqu = 10,
            zuneifan = 11,
            zuwaifan = 12,
        }

        public HermesROMTest()
        {
            _initFlag = -1;
            _angle_zhunzhi_l = -1; _angle_zhunzhi_r = -1;
            _angle_zhun_count_l = -1; _angle_zhun_count_r = -1;
            _angle_zhun_max_l = -1; _angle_zhun_max_r = -1;
            _angleOutput_l = -1; _angleOutput_r = -1;
            _rateOfProcess_l = -1; _rateOfProcess_r = -1;
            _angle_pian_l = -1; _angle_pian_r = -1;
            m_maxDuration_left = -1; m_anglePian_left = -1; m_whichone_left = -1; m_jindutiao_left = -1;
            m_maxDuration_right = -1; m_anglePian_right = -1; m_whichone_right = -1; m_jindutiao_right = -1;
        }

        public void reset(TestMathodName index)
        {
            _initFlag = 0;
            _angle_zhunzhi_l = 0; _angle_zhunzhi_r = 0;
            _angle_zhun_count_l = 0; _angle_zhun_count_r = 0;
            _angle_zhun_max_l = 0; _angle_zhun_max_r = 0;
            _angleOutput_l = 0; _angleOutput_r = 0;
            _rateOfProcess_l = 0; _rateOfProcess_r = 0;
            _angle_pian_l = 0; _angle_pian_r = 0;
            m_maxDuration_left = 0; m_anglePian_left = 0; m_whichone_left = -1; m_jindutiao_left = 0;
            m_maxDuration_right = 0; m_anglePian_right = 0; m_whichone_right = -1; m_jindutiao_right = 0;
            m_index = index;
        }

        bool waitForCurrectInitPose(
                                    float[] fArray,
                                    float[] range, int numberOfRange, float[] wrongNumber
                                    )
        {
            int waistNum = 0;
            int leftThighNum = 1; int rightThighNum = 2;
            int leftShinNum = 3; int rightShinNum = 4;
            int leftFootNum = 5; int rightFootNum = 6;
            int voidNum = 999;

            bool checkFlag = true;

            float[] w_array = new float[7], x_array = new float[7], y_array = new float[7], z_array = new float[7];
            for (int i = 0; i < 7; i++)
            {
                x_array[i] = fArray[4 * i + 0];
                y_array[i] = fArray[4 * i + 1];
                z_array[i] = fArray[4 * i + 2];
                w_array[i] = fArray[4 * i + 3];
            }

            for (int i = 0; i < numberOfRange; i++)
            {
                int type = (int)(range[ i * 3 + 2]);
                int rangeBottom = (int)range[ i * 3 + 0];
                int rangeTop = (int)range[ i * 3 + 1];
                float mainAngle = 0;
                bool isNotIn = false;
                switch (type)
                {
                    case 0:         //左侧膝关节的弯曲角度情况（函数直接得到）
                        mainAngle = reqMainAngleRelative(w_array[leftThighNum], x_array[leftThighNum], y_array[leftThighNum], z_array[leftThighNum], 2,
                            w_array[leftShinNum], x_array[leftShinNum], y_array[leftShinNum], z_array[leftShinNum], 2);
                        break;
                    case 1:         //右侧膝关节的弯曲角度情况（函数直接得到）
                        mainAngle = reqMainAngleRelative(w_array[rightThighNum], x_array[rightThighNum], y_array[rightThighNum], z_array[rightThighNum], 2,
                            w_array[rightShinNum], x_array[rightShinNum], y_array[rightShinNum], z_array[rightShinNum], 2);
                        break;
                    case 2:         //左侧小腿面(X)朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[leftShinNum], x_array[leftShinNum], y_array[leftShinNum], z_array[leftShinNum], 0,
                            1, 0, 0, 0, 2);
                        break;
                    case 3:         //右侧小腿面(X)朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[rightShinNum], x_array[rightShinNum], y_array[rightShinNum], z_array[rightShinNum], 0,
                            1, 0, 0, 0, 2);
                        break;
                    case 4:         //左侧脚面(X)朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[leftFootNum], x_array[leftFootNum], y_array[leftFootNum], z_array[leftFootNum], 0,
                            1, 0, 0, 0, 2);
                        break;
                    case 5:         //右侧脚面(X)朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[rightFootNum], x_array[rightFootNum], y_array[rightFootNum], z_array[rightFootNum], 0,
                            1, 0, 0, 0, 2);
                        break;
                    case 6:         //左侧大腿面与右侧大腿面(Z)之间夹角
                        mainAngle = reqMainAngleRelative(w_array[leftThighNum], x_array[leftThighNum], y_array[leftThighNum], z_array[leftThighNum], 2,
                                                         w_array[rightThighNum], x_array[rightThighNum], y_array[rightThighNum], z_array[rightThighNum], 2);
                        break;
                    case 7:         //左侧大腿面与右侧大腿面(X)之间夹角
                        mainAngle = reqMainAngleRelative(w_array[leftThighNum], x_array[leftThighNum], y_array[leftThighNum], z_array[leftThighNum], 0,
                                                         w_array[rightThighNum], x_array[rightThighNum], y_array[rightThighNum], z_array[rightThighNum], 0);
                        break;
                    case 8:         //左侧小腿面（Y）朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[leftShinNum], x_array[leftShinNum], y_array[leftShinNum], z_array[leftShinNum], 1,
                                                         1, 0, 0, 0, 2);
                        break;
                    case 9:         //右侧小腿面（Y）朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[rightShinNum], x_array[rightShinNum], y_array[rightShinNum], z_array[rightShinNum], 1,
                                                         1, 0, 0, 0, 2);
                        break;
                    case 10:         //髋关节（Z）朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[waistNum], x_array[waistNum], y_array[waistNum], z_array[waistNum], 2,
                                                         1, 0, 0, 0, 2);
                        break;
                    case 11:         //左小腿面（Y）朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[leftShinNum], x_array[leftShinNum], y_array[leftShinNum], z_array[leftShinNum], 1,
                                                         1, 0, 0, 0, 2);
                        break;
                    case 12:         //右小腿面（Y）朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[rightShinNum], x_array[rightShinNum], y_array[rightShinNum], z_array[rightShinNum], 1,
                                                         1, 0, 0, 0, 2);
                        break;
                    case 13:         //左小腿（Z）与髋关节(Y)夹角
                        mainAngle = reqMainAngleRelative(w_array[leftShinNum], x_array[leftShinNum], y_array[leftShinNum], z_array[leftShinNum], 2,
                                                         w_array[waistNum], x_array[waistNum], y_array[waistNum], z_array[waistNum], 1);
                        break;
                    case 14:         //右小腿（Z）与髋关节(Y)夹角
                        mainAngle = reqMainAngleRelative(w_array[rightShinNum], x_array[rightShinNum], y_array[rightShinNum], z_array[rightShinNum], 2,
                                                         w_array[waistNum], x_array[waistNum], y_array[waistNum], z_array[waistNum], 1);
                        break;
                    case 15:         //左小腿（Z）朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[leftShinNum], x_array[leftShinNum], y_array[leftShinNum], z_array[leftShinNum], 2,
                                                         1, 0, 0, 0, 2);
                        break;
                    case 16:         //右小腿（Z）朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[rightShinNum], x_array[rightShinNum], y_array[rightShinNum], z_array[rightShinNum], 2,
                                                         1, 0, 0, 0, 2);
                        break;
                    case 17:         //左大腿（Z）朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[leftThighNum], x_array[leftThighNum], y_array[leftThighNum], z_array[leftThighNum], 2,
                                                         1, 0, 0, 0, 2);
                        break;
                    case 18:         //右大腿（Z）朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[rightThighNum], x_array[rightThighNum], y_array[rightThighNum], z_array[rightThighNum], 2,
                                                         1, 0, 0, 0, 2);
                        break;
                    case 19:         //左脚（X）与右脚(X)夹角
                        mainAngle = reqMainAngleRelative(w_array[leftFootNum], x_array[leftFootNum], y_array[leftFootNum], z_array[leftFootNum], 0,
                                                         w_array[rightFootNum], x_array[rightFootNum], y_array[rightFootNum], z_array[rightFootNum], 0);
                        break;
                    case 20:         //左侧大腿（Z）与右大腿(Z)夹角
                        mainAngle = reqMainAngleRelative(w_array[leftThighNum], x_array[leftThighNum], y_array[leftThighNum], z_array[leftThighNum], 2,
                                                         w_array[rightThighNum], x_array[rightThighNum], y_array[rightThighNum], z_array[rightThighNum], 2);
                        break;
                    case 21:         //髋关节（X）朝向（与Z）
                        mainAngle = reqMainAngleRelative(w_array[waistNum], x_array[waistNum], y_array[waistNum], z_array[waistNum], 0,
                                                         1, 0, 0, 0, 2);
                        break;
                    default:
                        isNotIn = true;
                        break;
                }
                if (!isNotIn)
                {
                    if (mainAngle < rangeBottom || mainAngle > rangeTop)
                    {
                        checkFlag = false;
                        wrongNumber[type] = mainAngle;
                    }
                }
            }

            return checkFlag;
        }


        float maintainMaxAngle(float angle, float thresholdLow, float thresholdHigh, float delta, float count_final, 
                                ref float _rateOfProcess, ref float _angle_zhunzhi, ref float _angle_zhun_count, ref float _angle_zhun_max)
        {
            if (angle > thresholdHigh || angle < thresholdLow)
            {
                //不与准角度相同
                if (angle < _angle_zhunzhi - delta || angle > _angle_zhunzhi + delta)
                {
                    _angle_zhunzhi = angle;
                    _angle_zhun_count = 0;
                }
                else if (angle <= _angle_zhunzhi + delta && angle >= _angle_zhunzhi - delta)
                {
                    _angle_zhun_count++;
                }
            }
            if (angle >= thresholdLow && angle <= thresholdHigh)
            {
                _angle_zhun_count = 0;
                _angle_zhun_max = 0;
                _angle_zhunzhi = 0;
            }
            _rateOfProcess = (float)_angle_zhun_count / (float)rateOfProcessTotal * 100.0F;
            if (_angle_zhun_count == count_final)
            {
                if (Math.Abs(_angle_zhunzhi) > Math.Abs(_angle_zhun_max))
                {
                    _angle_zhun_max = _angle_zhunzhi;
                    return 500;
                }

            }
            return 0;
        }


        void ReqStandingSingleStraightLegRaise(                 //直膝屈髋样例
                                                float[] fArray,
                                                int firstIndex, int firstDirection, int secondIndex, int secondDirection, float mainAngleDelta, float pianAngleDelta,
                                                float[] undetectedRange, float mainAngle,
                                                ref float angle, ref float anglepian, ref float whichone, ref float rateOfProcess,
                                                float inputCompensation, float[] compensationRange,
                                                float[] range, int numberOfRange, float[] wrongNumber,
                                                ref float _rateOfProcess, ref float _angle_zhunzhi, ref float _angle_zhun_count, ref float _angle_zhun_max, ref float _angleOutput, ref float _angle_pian)
        {
            if (_initFlag == -1)
            {
                return;
            }
            float datuiAngle_com = -1; float angle_pian_com = -1;
            //    //---------------------半自动开始动作粗略检测---------------------
            bool isCorrect = waitForCurrectInitPose(fArray, range, numberOfRange, wrongNumber);
            if (!isCorrect) return;
            //    //---------------------异常监控---------------------------------
            //        //---------------------代偿计算----------------------------
            float compensationAngle = 0;
            //    compensationAngle = compensatoryCalculation(w_array, x_array, y_array, z_array, compensatoryIndex[0], compensatoryIndex[1], firstCompensatoryDirection, SecondCompensatoryDirection);
            if (inputCompensation != 0)
            {
                compensationAngle = 0;
                if (inputCompensation >= compensationRange[0] && inputCompensation <= compensationRange[1]) { }
                else if (inputCompensation > compensationRange[1])
                {
                    compensationAngle = inputCompensation - compensationRange[1];
                }
                else if (inputCompensation < compensationRange[0])
                {
                    compensationAngle = inputCompensation - compensationRange[0];
                }
            }
            //        //---------------------错误动作计算-----------------------
            //    int incorrectIndex[13] = { 0 };
            //    incorrectAngleCalculation(w_array, x_array, y_array, z_array, leftKneeRange, rightKneeRange,
            //        leftHipRange, rightHipRange,
            //        leftAnkleRange, rightAnkleRange,
            //        leftThighRange, rightThighRange,
            //        leftShinRange, rightShinRange,
            //        leftFootRange, rightFootRange,
            //        incorrectIndex);
            //---------------------某侧主要参数计算---------
            float[] w_array = new float[7], x_array = new float[7], y_array = new float[7], z_array = new float[7];
            for (int i = 0; i < 7; i++)
            {
                x_array[i] = fArray[4 * i + 0];
                y_array[i] = fArray[4 * i + 1];
                z_array[i] = fArray[4 * i + 2];
                w_array[i] = fArray[4 * i + 3];
            }

            float datuiAngle_zuo = 0;
            if (secondIndex == 999)
            {
                datuiAngle_zuo = reqMainAngleRelative(w_array[firstIndex], x_array[firstIndex],
                                                        y_array[firstIndex], z_array[firstIndex], firstDirection,
                                                        1, 0, 0, 0, secondDirection);
            }
            else if (firstIndex == 999)
            {
                datuiAngle_zuo = reqMainAngleRelative(1, 0, 0, 0, firstDirection,
                                                        w_array[secondIndex], x_array[secondIndex],
                                                        y_array[secondIndex], z_array[secondIndex], secondDirection);
            }
            else if (firstIndex <= 6 && secondIndex <= 6)
            {
                datuiAngle_zuo = reqMainAngleRelative(w_array[firstIndex], x_array[firstIndex],
                                                        y_array[firstIndex], z_array[firstIndex], firstDirection,
                                                        w_array[secondIndex], x_array[secondIndex],
                                                        y_array[secondIndex], z_array[secondIndex], secondDirection);
            }

            if (mainAngle != 0)
            {
                datuiAngle_zuo = mainAngle;
            }

            //---------------------某侧次要参数计算 Pian Angle----------R0.adjoint()*R1
            //Quat_t quat4 = new Quat_t( w4, x4, y4, z4 );
            Quat_t quat_left = new Quat_t(w_array[firstIndex], x_array[firstIndex], y_array[firstIndex], z_array[firstIndex] );
            Quat_t quat_base_left = new Quat_t(w_array[secondIndex], x_array[secondIndex], y_array[secondIndex], z_array[secondIndex] );
            Quat_t qzuo = new Quat_t(0, 0, 0, 0 );
            reqRotationQuat(quat_left, quat_base_left, out qzuo);
            float angle_pian_zuo = reqPianAngle(qzuo);

            //------------------------------------------------------------------------------
            datuiAngle_com = datuiAngle_zuo + mainAngleDelta;
            angle_pian_com = angle_pian_zuo + pianAngleDelta;
            _angleOutput = datuiAngle_com;
            whichone = -1;
            float tmp_rateOfProcess=0;
            if (maintainMaxAngle(datuiAngle_com, undetectedRange[0], undetectedRange[1], deltaAngle, delayCount,
                        ref  _rateOfProcess, ref  _angle_zhunzhi, ref  _angle_zhun_count, ref  _angle_zhun_max) == 500)
            {
                if (datuiAngle_com > undetectedRange[1] || datuiAngle_com < undetectedRange[0])
                {
                    whichone = 1;
                }
            }
            angle = _angle_zhun_max - compensationAngle;
            anglepian = _angle_pian;
            rateOfProcess = tmp_rateOfProcess;
        }

        public void calculationSingleTime(float[] floatArray, int lineIndex)
        {
            float[] imuCurrentW = new float[7], imuCurrentX = new float[7], imuCurrentY = new float[7], imuCurrentZ = new float[7];
            for (int i = 0; i < 7; i++)
            {
                imuCurrentX[i] = floatArray[4 * i + 0];
                imuCurrentY[i] = floatArray[4 * i + 1];
                imuCurrentZ[i] = floatArray[4 * i + 2];
                imuCurrentW[i] = floatArray[4 * i + 3];
            }
            int bodyIndex1 = 3; int bodyIndex2 = 5;

            if (m_index == TestMathodName.zubeiqu)
            {
                //踝关节柔韧性测试参数1(左腿向后）
                bodyIndex1 = 3; bodyIndex2 = 5;
                range = new float[]{ -170, 10.0F };
                wrongRange = new float[]{-15, 15, 0,
                                              -15, 15, 1,
                                              -20, 20, 2,
                                              -20, 20, 3,
                                              -20, 20, 5};
                wrongNumber = new float[5];
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 0, bodyIndex2, 2, -90, 0,
                                                    range, 0,
                                                    ref m_maxDuration_left, ref m_anglePian_left, ref m_whichone_left, ref m_jindutiao_left,
                                                     0, null, wrongRange, 5, wrongNumber,
                                                    ref _rateOfProcess_l, ref _angle_zhunzhi_l, ref _angle_zhun_count_l, ref _angle_zhun_max_l, ref _angleOutput_l, ref _angle_pian_l);


                //踝关节柔韧性测试参数1(右腿向后）
                bodyIndex1 = 4; bodyIndex2 = 6;
                range = new float[] { -170, 10.0F };
                wrongRange = new float[]{-15, 15, 0,
                                              -15, 15, 1,
                                              -20, 20, 2,
                                              -20, 20, 3,
                                              -20, 20, 4};
                wrongNumber = new float[5];
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 0, bodyIndex2, 2, -90, 0,
                                                    range, 0,
                                                    ref m_maxDuration_right, ref m_anglePian_right, ref m_whichone_right, ref m_jindutiao_right,
                                                     0, null, wrongRange, 5, wrongNumber,
                                                     ref _rateOfProcess_r, ref _angle_zhunzhi_r, ref _angle_zhun_count_r, ref _angle_zhun_max_r, ref _angleOutput_r, ref _angle_pian_r);
            }
            else if(m_index == TestMathodName.zuzhiqu)
            {
                //踝关节柔韧性测试参数2(左腿向前）
                bodyIndex1 = 3; bodyIndex2 = 5;
                range = new float[] { -15.0F, 170 };
                wrongRange = new float[]{-15, 15, 0,
                                        -15, 15, 1,
                                        -20, 20, 2,
                                        -20, 20, 3,
                                        -20, 20, 5};
                wrongNumber = new float[5];
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 0, bodyIndex2, 2, -90, 0,
                                                    range, 0,
                                                    ref m_maxDuration_left, ref m_anglePian_left, ref m_whichone_left, ref m_jindutiao_left,
                                                     0, null, wrongRange, 5, wrongNumber,
                                                     ref _rateOfProcess_l, ref _angle_zhunzhi_l, ref _angle_zhun_count_l, ref _angle_zhun_max_l, ref _angleOutput_l, ref _angle_pian_l);

                //踝关节柔韧性测试参数2(右腿向前）
                bodyIndex1 = 4; bodyIndex2 = 6;
                range = new float[] { -15.0F, 170 };
                wrongRange = new float[]{-15, 15, 0,
                                        -15, 15, 1,
                                        -20, 20, 2,
                                        -20, 20, 3,
                                        -20, 20, 4};
                wrongNumber = new float[5];
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 0, bodyIndex2, 2, -90, 0,
                                                    range, 0,
                                                    ref m_maxDuration_right, ref m_anglePian_right, ref m_whichone_right, ref m_jindutiao_right,
                                                     0, null, wrongRange, 5, wrongNumber,
                                                     ref _rateOfProcess_r, ref _angle_zhunzhi_r, ref _angle_zhun_count_r, ref _angle_zhun_max_r, ref _angleOutput_r, ref _angle_pian_r);
            }
            else if(m_index == TestMathodName.quxi)
            {
                //膝盖关节柔韧性测试参数1(左腿）
                bodyIndex1 = 1; bodyIndex2 = 3;
                range = new float[] { -170, 30 };
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                    range, 0,
                                                    ref m_maxDuration_left, ref m_anglePian_left, ref m_whichone_left, ref m_jindutiao_left,
                                                     0, null, null, 0, null,
                                                     ref _rateOfProcess_l, ref _angle_zhunzhi_l, ref _angle_zhun_count_l, ref _angle_zhun_max_l, ref _angleOutput_l, ref _angle_pian_l);

                //膝盖关节柔韧性测试参数1(右腿）
                bodyIndex1 = 2; bodyIndex2 = 4;
                range = new float[] { -170, 30 };
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                    range, 0,
                                                    ref m_maxDuration_right, ref m_anglePian_right, ref m_whichone_right, ref m_jindutiao_right,
                                                     0, null, null, 0, null,
                                                     ref _rateOfProcess_r, ref _angle_zhunzhi_r, ref _angle_zhun_count_r, ref _angle_zhun_max_r, ref _angleOutput_r, ref _angle_pian_r);
            }
            else if(m_index == TestMathodName.zhixiqukuan || m_index == TestMathodName.zhixiqukuanFuzhu)
            {
                //髋关节柔韧性测试参数1(左脚）
                bodyIndex1 = 1; bodyIndex2 = 2;
                range = new float[] { -170.0F, 25 };
                wrongRange = new float[] {90-25, 90+25, 11,
                                              90-25, 90+25, 12,
                                              90-15, 90+15, 13,
                                              90-15, 90+15, 14,
                                              -25, +25, 0,
                                              -25, +25, 1,};
                wrongNumber = new float[6];
                float[] compens = new float[] { -10, 10 };
                float daichang = reqMainAngleRelative(imuCurrentW[0], imuCurrentX[0], imuCurrentY[0], imuCurrentZ[0], 0,
                                     1, 0, 0, 0, 2);

                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                    range, 0,
                                                    ref m_maxDuration_left, ref m_anglePian_left, ref m_whichone_left, ref m_jindutiao_left,
                                                     90.0F - daichang, compens,
                                                     wrongRange, 6, wrongNumber,
                                                     ref _rateOfProcess_l, ref _angle_zhunzhi_l, ref _angle_zhun_count_l, ref _angle_zhun_max_l, ref _angleOutput_l, ref _angle_pian_l);

                //髋关节柔韧性测试参数1(右脚）
                bodyIndex1 = 2; bodyIndex2 = 1;
                range = new float[] { -170.0F, 25 };
                wrongRange = new float[]{90-25, 90+25, 11,
                                              90-25, 90+25, 12,
                                              90-15, 90+15, 13,
                                              90-15, 90+15, 14,
                                              -25, +25, 0,
                                              -25, +25, 1,};
                wrongNumber = new float[6] ;
                compens = new float[] { -10, 10 };
                daichang = reqMainAngleRelative(imuCurrentW[0], imuCurrentX[0], imuCurrentY[0], imuCurrentZ[0], 0,
                                     1, 0, 0, 0, 2);
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                   range, 0,
                                                   ref m_maxDuration_right, ref m_anglePian_right, ref m_whichone_right, ref m_jindutiao_right,
                                                    90.0F - daichang, compens,
                                                    wrongRange, 6, wrongNumber,
                                                    ref _rateOfProcess_r, ref _angle_zhunzhi_r, ref _angle_zhun_count_r, ref _angle_zhun_max_r, ref _angleOutput_r, ref _angle_pian_r);
            }
            else if (m_index == TestMathodName.housheng || m_index == TestMathodName.houshengFuzhu)
            {
                //髋关节柔韧性测试参数2（左）（后伸）
                bodyIndex1 = 1; bodyIndex2 = 2;
                range = new float[] { -170.0F, 25 };
                wrongRange = new float[]{0-60, 0+60, 20,
                                                -20, +20, 0,
                                                -20, +20, 1,
                                            90-10, 90+20, 15,
                                            90-10, 90+20, 17,
                                            180-30, 90+30, 21
                                             };
                wrongNumber = new float[6];
                for (int i = 0; i < 30; i++)
                {
                    wrongNumber[i] = -1000;
                }
                float[] compens = new float[2] { -5, 5 };
                float daichang = 90 - reqMainAngleRelative(imuCurrentW[0], imuCurrentX[0], imuCurrentY[0], imuCurrentZ[0], 1,
                                     1, 0, 0, 0, 2);
                if (daichang < 0) daichang = -daichang;
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                    range, 0,
                                                    ref m_maxDuration_left, ref m_anglePian_left, ref m_whichone_left, ref m_jindutiao_left,
                                                     daichang, compens,
                                                     wrongRange, 6, wrongNumber,
                                                     ref _rateOfProcess_l, ref _angle_zhunzhi_l, ref _angle_zhun_count_l, ref _angle_zhun_max_l, ref _angleOutput_l, ref _angle_pian_l);


                //髋关节柔韧性测试参数2（右）（后伸）
                bodyIndex1 = 1; bodyIndex2 = 2;
                range = new float[] { -170.0F, 25 };
                wrongRange = new float[] {0-60, 0+60, 20,
                                                -20, +20, 0,
                                                -20, +20, 1,
                                            90-10, 90+20, 16,
                                            90-10, 90+20, 18,
                                            180-30, 180+30, 21
                                             };
                wrongNumber = new float[6];
                for (int i = 0; i < 6; i++)
                {
                    wrongNumber[i] = -1000;
                }
                compens = new float[2] { -5, 5 };
                daichang = 90 - reqMainAngleRelative(imuCurrentW[0], imuCurrentX[0], imuCurrentY[0], imuCurrentZ[0], 1,
                                     1, 0, 0, 0, 2);
                if (daichang < 0) daichang = -daichang;
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                   range, 0,
                                                   ref m_maxDuration_right, ref m_anglePian_right, ref m_whichone_right, ref m_jindutiao_right,
                                                    daichang, compens,
                                                    wrongRange, 6, wrongNumber,
                                                    ref _rateOfProcess_r, ref _angle_zhunzhi_r, ref _angle_zhun_count_r, ref _angle_zhun_max_r, ref _angleOutput_r, ref _angle_pian_r);

            }
            else if (m_index == TestMathodName.kuanwaizhan)
            {
                //髋关节柔韧性测试参数3（左脚）(外展）
                bodyIndex1 = 1; bodyIndex2 = 2;
                range = new float[] { -170.0F, 10 };
                wrongRange = new float[]{90-15, 90+15, 15,
                                              90-15, 90+15, 16,
                                              90-15, 90+15, 17,
                                              90-15, 90+15, 18,
                                                -15, +15, 0,
                                                -15, +15, 1};
                wrongNumber = new float[6];
                for (int i = 0; i < 6; i++)
                {
                    wrongNumber[i] = -1000;
                }
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                   range, 0,
                                                   ref m_maxDuration_left, ref m_anglePian_left, ref m_whichone_left, ref m_jindutiao_left,
                                                    0, null, wrongRange, 6, wrongNumber,
                                                    ref _rateOfProcess_l, ref _angle_zhunzhi_l, ref _angle_zhun_count_l, ref _angle_zhun_max_l, ref _angleOutput_l, ref _angle_pian_l);

                //髋关节柔韧性测试参数3（右脚）(外展）
                bodyIndex1 = 1; bodyIndex2 = 2;
                range = new float[] { -170.0F, 10 };
                wrongRange = new float[]{90-15, 90+15, 15,
                                              90-15, 90+15, 16,
                                              90-15, 90+15, 17,
                                              90-15, 90+15, 18,
                                                -15, +15, 0,
                                                -15, +15, 1};
                wrongNumber = new float[6];
                for (int i = 0; i < 6; i++)
                {
                    wrongNumber[i] = -1000;
                }
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 0, bodyIndex2, 2, 0, 0,
                                                    range, 0,
                                                    ref m_maxDuration_right, ref m_anglePian_right, ref m_whichone_right, ref m_jindutiao_right,
                                                     0, null, wrongRange, 6, wrongNumber,
                                                     ref _rateOfProcess_r, ref _angle_zhunzhi_r, ref _angle_zhun_count_r, ref _angle_zhun_max_r, ref _angleOutput_r, ref _angle_pian_r);
            }
            else if (m_index == TestMathodName.kuanneishou)
            {
                //髋关节柔韧性测试参数4（左腿站，右腿做）
                bodyIndex1 = 1; bodyIndex2 = 2;
                range = new float[] { -170.0F, 10 };
                wrongRange = new float[]{0-15, 0+19, 15,
                                              0-15, 0+19, 17,
                                              0-15, 0+45, 16,
                                              0-15, 0+45, 18,
                                                -15, +15, 0,
                                                -15, +30, 1,
                                                 -30, 30, 19};
                wrongNumber = new float[7];
                for (int i = 0; i < 7; i++)
                {
                    wrongNumber[i] = -1000;
                }
                float[] compens = new float[] { -10, 20 };
                float mainAngle = reqMainAngleRelative(imuCurrentW[bodyIndex1], imuCurrentX[bodyIndex1], imuCurrentY[bodyIndex1], imuCurrentZ[bodyIndex1], 2,
                                     imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2);
                float sign = reqMainAngleRelative(imuCurrentW[bodyIndex1], imuCurrentX[bodyIndex1], imuCurrentY[bodyIndex1], imuCurrentZ[bodyIndex1], 1,
                                     imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2) - 90;
                if (sign < 0) mainAngle = -mainAngle;
                float daichang = reqMainAngleRelative(imuCurrentW[bodyIndex1], imuCurrentX[bodyIndex1], imuCurrentY[bodyIndex1], imuCurrentZ[bodyIndex1], 0,
                                     imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2) - 90;
                if (daichang < 0) daichang = 100;
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 1, bodyIndex2, 2, 0, 0,
                                                    range, mainAngle,
                                                    ref m_maxDuration_left, ref m_anglePian_left, ref m_whichone_left, ref m_jindutiao_left,
                                                     daichang, compens,
                                                     wrongRange, 7, wrongNumber,
                                                     ref _rateOfProcess_l, ref _angle_zhunzhi_l, ref _angle_zhun_count_l, ref _angle_zhun_max_l, ref _angleOutput_l, ref _angle_pian_l);


                //髋关节柔韧性测试参数4（右腿站，左腿做）
                bodyIndex1 = 2; bodyIndex2 = 1;
                range = new float[] { -170.0F, 10 };
                wrongRange = new float[]{0-15, 0+18, 16,
                                              0-15, 0+18, 18,
                                              0-15, 0+45, 15,
                                              0-15, 0+45, 17,
                                                -15, +30, 0,
                                                -15, +15, 1,
                                                 -30, 30, 19};
                wrongNumber = new float[7];
                for (int i = 0; i < 7; i++)
                {
                    wrongNumber[i] = -1000;
                }
                compens = new float[] { -10, 20 };
                mainAngle = reqMainAngleRelative(imuCurrentW[bodyIndex1], imuCurrentX[bodyIndex1], imuCurrentY[bodyIndex1], imuCurrentZ[bodyIndex1], 2,
                                     imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2);
                sign = reqMainAngleRelative(imuCurrentW[bodyIndex1], imuCurrentX[bodyIndex1], imuCurrentY[bodyIndex1], imuCurrentZ[bodyIndex1], 1,
                                     imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2) - 90;
                if (sign > 0) mainAngle = -mainAngle;
                daichang = reqMainAngleRelative(imuCurrentW[bodyIndex1], imuCurrentX[bodyIndex1], imuCurrentY[bodyIndex1], imuCurrentZ[bodyIndex1], 0,
                                     imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2) - 90;
                //criterial = reqMainAngleRelative(imuCurrentW[4], imuCurrentX[4], imuCurrentY[4], imuCurrentZ[4], 0,
                //                     1, 0, 0, 0, 2) - reqMainAngleRelative(imuCurrentW[3], imuCurrentX[3], imuCurrentY[3], imuCurrentZ[3], 0, 1, 0, 0, 0, 2);
                if (daichang < 0) daichang = 100;
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 1, bodyIndex2, 2, 0, 0,
                                                   range, mainAngle,
                                                   ref m_maxDuration_right, ref m_anglePian_right, ref m_whichone_right, ref m_jindutiao_right,
                                                    daichang, compens,
                                                    wrongRange, 7, wrongNumber,
                                                    ref _rateOfProcess_r, ref _angle_zhunzhi_r, ref _angle_zhun_count_r, ref _angle_zhun_max_r, ref _angleOutput_r, ref _angle_pian_r);

            }
            else if (m_index == TestMathodName.kuanwaixuan)
            {
                //髋关节柔韧性测试参数5(右腿摆）向外
                bodyIndex1 = 999; bodyIndex2 = 4;
                range = new float[] { -170, 10 };
                wrongRange = new float[]{0-10, 0+10, 20,
                                                -20, +20, 0,
                                            90-20, 90+20, 1,
                                            90-10, 90+20, 16,
                                            90-10, 90+20, 17,
                                            90-10, 90+20, 18,
                                            180-30, 90+30, 21
                                             };
                wrongNumber = new float[7];
                for (int i = 0; i < 7; i++)
                {
                    wrongNumber[i] = -1000;
                }
                float[] compens = new float[] { -10, 10 };
                float mainAngle = 180 - reqMainAngleRelative(imuCurrentW[bodyIndex1], imuCurrentX[bodyIndex1], imuCurrentY[bodyIndex1], imuCurrentZ[bodyIndex1], 2,
                                     imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2);
                float[] nVector = new float[3];
                reqCrossProduct(imuCurrentW[1], imuCurrentX[1],
                                imuCurrentY[1], imuCurrentZ[1], 2,
                                1, 0,
                                0, 0, 2, out nVector);
                float sign = reqMainAngleRelativeEXFirst(nVector[0], nVector[1], nVector[2], imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2) - 90;
                if (sign < 0) mainAngle = -mainAngle;
                float daichang = reqMainAngleRelative(imuCurrentW[2], imuCurrentX[2], imuCurrentY[2], imuCurrentZ[2], 2,
                                     imuCurrentW[4], imuCurrentX[4], imuCurrentY[4], imuCurrentZ[4], 2);
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                    range, mainAngle,
                                                    ref m_maxDuration_left, ref m_anglePian_left, ref m_whichone_left, ref m_jindutiao_left,
                                                     daichang - 90, compens,
                                                     wrongRange, 7, wrongNumber,
                                                     ref _rateOfProcess_l, ref _angle_zhunzhi_l, ref _angle_zhun_count_l, ref _angle_zhun_max_l, ref _angleOutput_l, ref _angle_pian_l);

                //髋关节柔韧性测试参数5(左腿摆）向外
                bodyIndex1 = 999; bodyIndex2 = 3;
                range = new float[] { -10, 170 };
                wrongRange = new float[]{0-10, 0+10, 20,
                                                -20, +20, 0,
                                            90-20, 90+20, 1,
                                            90-10, 90+20, 16,
                                            90-10, 90+20, 17,
                                            90-10, 90+20, 18,
                                            180-30, 90+30, 21
                                             };
                wrongNumber = new float[7];
                for (int i = 0; i < 7; i++)
                {
                    wrongNumber[i] = -1000;
                }
                compens = new float[] { -10, 10 };
                mainAngle = 180 - reqMainAngleRelative(imuCurrentW[bodyIndex1], imuCurrentX[bodyIndex1], imuCurrentY[bodyIndex1], imuCurrentZ[bodyIndex1], 2,
                                     imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2);
                nVector = new float[3];
                reqCrossProduct(imuCurrentW[2], imuCurrentX[2],
                                imuCurrentY[2], imuCurrentZ[2], 2,
                                1, 0,
                                0, 0, 2, out nVector);
                sign = reqMainAngleRelativeEXFirst(nVector[0], nVector[1], nVector[2], imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2) - 90;
                if (sign < 0) mainAngle = -mainAngle;
                daichang = reqMainAngleRelative(imuCurrentW[1], imuCurrentX[1], imuCurrentY[1], imuCurrentZ[1], 2,
                                     imuCurrentW[3], imuCurrentX[3], imuCurrentY[3], imuCurrentZ[3], 2);
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                   range, mainAngle,
                                                   ref m_maxDuration_right, ref m_anglePian_right, ref m_whichone_right, ref m_jindutiao_right,
                                                    daichang - 90, compens,
                                                    wrongRange, 7, wrongNumber,
                                                    ref _rateOfProcess_r, ref _angle_zhunzhi_r, ref _angle_zhun_count_r, ref _angle_zhun_max_r, ref _angleOutput_r, ref _angle_pian_r);
            }
            else if (m_index == TestMathodName.kuanneixuan)
            {
                //髋关节柔韧性测试参数5(右腿摆）向内
                bodyIndex1 = 999; bodyIndex2 = 4;
                range = new float[] { -20, 170 };
                wrongRange = new float[]{0-10, 0+10, 20,
                                                -20, +20, 0,
                                            90-20, 90+20, 1,
                                            90-10, 90+20, 16,
                                            90-10, 90+20, 17,
                                            90-10, 90+20, 18,
                                            180-30, 90+30, 21
                                             };
                wrongNumber = new float[7];
                for (int i = 0; i < 7; i++)
                {
                    wrongNumber[i] = -1000;
                }
                float[] compens = new float[] { -20, 10 };
                float mainAngle = 180 - reqMainAngleRelative(imuCurrentW[bodyIndex1], imuCurrentX[bodyIndex1], imuCurrentY[bodyIndex1], imuCurrentZ[bodyIndex1], 2,
                                     imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2);
                float[] nVector = new float[3];
                reqCrossProduct(imuCurrentW[1], imuCurrentX[1],
                                imuCurrentY[1], imuCurrentZ[1], 2,
                                1, 0,
                                0, 0, 2, out nVector);
                float sign = reqMainAngleRelativeEXFirst(nVector[0], nVector[1], nVector[2], imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2) - 90;
                if (sign < 0) mainAngle = -mainAngle;
                float daichang = reqMainAngleRelative(imuCurrentW[2], imuCurrentX[2], imuCurrentY[2], imuCurrentZ[2], 2,
                                     imuCurrentW[4], imuCurrentX[4], imuCurrentY[4], imuCurrentZ[4], 2);
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                    range, mainAngle,
                                                    ref m_maxDuration_left, ref m_anglePian_left, ref m_whichone_left, ref m_jindutiao_left,
                                                     daichang - 90, compens,
                                                     wrongRange, 7, wrongNumber,
                                                     ref _rateOfProcess_l, ref _angle_zhunzhi_l, ref _angle_zhun_count_l, ref _angle_zhun_max_l, ref _angleOutput_l, ref _angle_pian_l);

                //髋关节柔韧性测试参数5(左腿摆）向内
                bodyIndex1 = 999; bodyIndex2 = 3;
                range = new float[] { -170, 20 };
                wrongRange = new float[]{0-10, 0+10, 20,
                                                -20, +20, 0,
                                            90-20, 90+20, 1,
                                            90-10, 90+20, 16,
                                            90-10, 90+20, 17,
                                            90-10, 90+20, 18,
                                            180-30, 90+30, 21
                                             };
                wrongNumber = new float[7];
                for (int i = 0; i < 7; i++)
                {
                    wrongNumber[i] = -1000;
                }
                compens = new float[] { -10, 10 };
                mainAngle = 180 - reqMainAngleRelative(imuCurrentW[bodyIndex1], imuCurrentX[bodyIndex1], imuCurrentY[bodyIndex1], imuCurrentZ[bodyIndex1], 2,
                                     imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2);
                nVector = new float[3];
                reqCrossProduct(imuCurrentW[2], imuCurrentX[2],
                                imuCurrentY[2], imuCurrentZ[2], 2,
                                1, 0,
                                0, 0, 2, out nVector);
                sign = reqMainAngleRelativeEXFirst(nVector[0], nVector[1], nVector[2], imuCurrentW[bodyIndex2], imuCurrentX[bodyIndex2], imuCurrentY[bodyIndex2], imuCurrentZ[bodyIndex2], 2) - 90;
                if (sign < 0) mainAngle = -mainAngle;
                daichang = reqMainAngleRelative(imuCurrentW[1], imuCurrentX[1], imuCurrentY[1], imuCurrentZ[1], 2,
                                     imuCurrentW[3], imuCurrentX[3], imuCurrentY[3], imuCurrentZ[3], 2);
                ReqStandingSingleStraightLegRaise(floatArray, bodyIndex1, 2, bodyIndex2, 2, 0, 0,
                                                   range, mainAngle,
                                                   ref m_maxDuration_right, ref m_anglePian_right, ref m_whichone_right, ref m_jindutiao_right,
                                                    daichang - 90, compens,
                                                    wrongRange, 7, wrongNumber,
                                                    ref _rateOfProcess_r, ref _angle_zhunzhi_r, ref _angle_zhun_count_r, ref _angle_zhun_max_r, ref _angleOutput_r, ref _angle_pian_r);
            }
            else
            {

            }

            


        }
    }    //新版关节灵活度测试，主要类

    public class HermesCalculator
    {
        public static float PI = 3.14159265358979323846F;

        //初始化函数
        public HermesCalculator()
        {

        }

        public static float reqMainAngleRelative(float w0, float x0, float y0, float z0, int direction0,
                           float w, float x, float y, float z, int direction)
        {
            float l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            switch (direction)
            {
                case 0:      //X方向
                    o = 1 - 2 * y * y - 2 * z * z;
                    p = 2 * x * y + 2 * w * z;
                    q = 2 * x * z - 2 * w * y;
                    break;
                case 1:      //Y方向
                    o = 2 * x * y - 2 * w * z;
                    p = 1 - 2 * x * x - 2 * z * z;
                    q = 2 * y * z + 2 * w * x;
                    break;
                case 2:      //Z方向
                    o = 2 * x * z + 2 * w * y;
                    p = 2 * y * z - 2 * w * x;
                    q = 1 - 2 * x * x - 2 * y * y;
                    break;
                default:
                    break;
            }
            //    float Angle = sqrt((m*q - n * p)*(m*q - n * p) + (n*o - l * q)*(n*o - l * q) + (l*p - m * o)*(l*p - m * o));
            //    Angle = asin(Angle) / PI * 180;
            float inner = l * o + m * p + n * q;
            if (inner > 1.000) inner = 1.000F;
            else if (inner < -1.000) inner = -1.000F;
            float Angle = (float)Math.Acos(inner) / PI * 180;
            return Angle;
        }


        public static float[] reqMainAnglePosition(float w0, float x0, float y0, float z0, int direction0)
        {
            float l = 0, m = 0, n = 0, o = 0, p = 0, q = 0;
            switch (direction0)
            {
                case 0:      //X方向
                    l = 1 - 2 * y0 * y0 - 2 * z0 * z0;
                    m = 2 * x0 * y0 + 2 * w0 * z0;
                    n = 2 * x0 * z0 - 2 * w0 * y0;
                    break;
                case 1:      //Y方向
                    l = 2 * x0 * y0 - 2 * w0 * z0;
                    m = 1 - 2 * x0 * x0 - 2 * z0 * z0;
                    n = 2 * y0 * z0 + 2 * w0 * x0;
                    break;
                case 2:      //Z方向
                    l = 2 * x0 * z0 + 2 * w0 * y0;
                    m = 2 * y0 * z0 - 2 * w0 * x0;
                    n = 1 - 2 * x0 * x0 - 2 * y0 * y0;
                    break;
                default:
                    break;
            }
            //    float Angle = sqrt((m*q - n * p)*(m*q - n * p) + (n*o - l * q)*(n*o - l * q) + (l*p - m * o)*(l*p - m * o));
            //    Angle = asin(Angle) / PI * 180;
            float[] ret = new float[3];
            ret[0] = 20 * l;
            ret[1] = 20 * m;
            ret[2] = 20 * n;
            return ret;
        }


        public static float[] reqProjectionVectorToASurface(float ax, float ay, float az,
                                                            float sx1, float sy1, float sz1,
                                                            float sx2, float sy2, float sz2)
        {
            double l = sx1;
            double m = sy1;
            double n = sz1;
            double o = sx2;
            double p = sy2;
            double q = sz2;
            double nx = m * q - n * p;
            double ny = n * o - l * q;
            double nz = l * p - m * o;

            double inner = (ax * nx + ay * ny + az * nz) / Math.Sqrt(ax * ax + ay * ay + az * az) / Math.Sqrt(nx * nx + ny * ny + nz * nz);
            double x = ax / Math.Sqrt(ax * ax + ay * ay + az * az) - inner * nx / Math.Sqrt(nx * nx + ny * ny + nz * nz);
            double y = ay / Math.Sqrt(ax * ax + ay * ay + az * az) - inner * ny / Math.Sqrt(nx * nx + ny * ny + nz * nz);
            double z = az / Math.Sqrt(ax * ax + ay * ay + az * az) - inner * nz / Math.Sqrt(nx * nx + ny * ny + nz * nz);

            float[] ret = new float[3];
            ret[0] = (float)x;
            ret[1] = (float)y;
            ret[2] = (float)z;
            return ret;
        }

        public static float[] reqNVector(float sx1, float sy1, float sz1,
                                         float sx2, float sy2, float sz2)
        {
            double l = sx1;
            double m = sy1;
            double n = sz1;
            double o = sx2;
            double p = sy2;
            double q = sz2;
            double nx = (m * q - n * p);
            double ny = (n * o - l * q);
            double nz = (l * p - m * o);

            double nxx = nx / Math.Sqrt(nx * nx + ny * ny + nz * nz);
            double nyy = ny / Math.Sqrt(nx * nx + ny * ny + nz * nz);
            double nzz = nz / Math.Sqrt(nx * nx + ny * ny + nz * nz);

            float[] ret = new float[3];
            ret[0] = (float)nxx;
            ret[1] = (float)nyy;
            ret[2] = (float)nzz;
            return ret;
        }

        public static float reqMainAngleLMNRelative(float l, float m, float n,
                                                    float o, float p, float q)
        {
            double inner = (l * o + m * p + n * q) / Math.Sqrt(l * l + m * m + n * n) / Math.Sqrt(o * o + p * p + q * q);
            double innerchange = 0;

            if (inner > 1.000)
            {
                innerchange = 1.000;
            }
                
            else if (inner< -1.000)
            {
                innerchange = -1.000;
            }
            else
            {
                innerchange = inner;
            }
            float ret = (float)Math.Acos(innerchange) / PI * 180;
            return ret;
        }


        public static float reqQuShengAngle(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);
            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu_b[0], yaobu_b[1], yaobu_b[2], 0, 0, 1);
            float[] yaobu_proj = new float[3];
            yaobu_proj = reqProjectionVectorToASurface(yaobu[0], yaobu[1], yaobu[2], yaobu_b[0], yaobu_b[1], yaobu_b[2], 0, 0, 1);
            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0], yaobu_proj[1], yaobu_proj[2]);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], yaobu_yd[1], yaobu_yd[2]);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0], yaobu_proj[1], yaobu_proj[2]);
            }  
            else if (aaa -40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0], yaobu_proj[1], yaobu_proj[2]);
            }
            return angle;
        }        //膝盖屈伸，+为伸，-为屈

        public static float reqQuShengAngleToGround(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu_b[0], yaobu_b[1], yaobu_b[2], 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], yaobu_yd[1], yaobu_yd[2]);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            return angle;
        }   //髋关节屈伸，-为伸，+为屈

        public static float reqXiaotuiToGroundAngle(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(1, 0, 0, 0, 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu_b[0]*1, yaobu_b[1]*0, yaobu_b[2]*0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0]*0, yaobu_yd[1], yaobu_yd[2]*0);

            float angle = 0;
            if (aaa > 10)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            else if (aaa  < 10)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            return angle;
        }

        public static float reqZuToGroundAngle(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_y = new float[3];
            yaobu_y = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 0);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 1, 0, 0, 0, 1, 0);
            float[] yaobu_y_proj = new float[3];
            yaobu_y_proj = reqProjectionVectorToASurface(yaobu_y[0], yaobu_y[1], yaobu_y[2], 1, 0, 0, 0, 1, 0);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], zuodatui[0], zuodatui[1], zuodatui[2]);

            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_y_proj[0], yaobu_y_proj[1], yaobu_y_proj[2]);

            float angle = 0;
            if (aaa > 90)
            {
                angle = reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], zuodatui[0], zuodatui[1], zuodatui[2]);
            }
            else if (aaa < 90)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], zuodatui[0], zuodatui[1], zuodatui[2]);
            }
            return angle;
        }

        public static float reqZuQuShengAngle(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(1, 0, 0, 0, 0);

            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 0);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu_b[0], yaobu_b[1], yaobu_b[2], 0, 0, 1);

            float[] yaobu_proj = new float[3];
            yaobu_proj = reqProjectionVectorToASurface(yaobu[0], yaobu[1], yaobu[2], yaobu_b[0], yaobu_b[1], yaobu_b[2], 0, 0, 1);

            float angle = 0;
            angle = 90 - reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0], yaobu_proj[1], yaobu_proj[2]);
            return angle;
        }

        public static float reqZuNeifanWaifanAngle3(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 1);

            float[] yaobu_b_2 = new float[3];
            yaobu_b_2 = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);

            float[] yaobu_b_0 = new float[3];
            yaobu_b_0 = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 1);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu_b[0], yaobu_b[1], yaobu_b[2], yaobu_b_2[0], yaobu_b_2[1], yaobu_b_2[2]);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_2[0], yaobu_b_2[1], yaobu_b_2[2]);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_b_0[0], yaobu_b_0[1], yaobu_b_0[2]);

            float angle = 0;
            if (aaa - 40 > 0)
            {
                angle = reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_2[0], yaobu_b_2[1], yaobu_b_2[2]) + 90;
            }
            else if (aaa - 40 <= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_2[0], yaobu_b_2[1], yaobu_b_2[2]) + 90;
            }
            return angle;
        }        //左侧外翻为+，内翻-， 右侧内翻为+，外翻-

        public static float reqZuNeixuanWaixuanAngle4(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 0);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 1, 0, 0, 0, 1, 0);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0] * 1, yaobu_b[1] * 0, yaobu_b[2] * 0);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0] * 0, yaobu_yd[1] * 0, yaobu_yd[2] * 1);

            float angle = 0;
            if (aaa - 20 <= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0] * 1, yaobu_b[1] * 0, yaobu_b[2] * 0);
            }
            else if (aaa - 20 > 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0] * 1, yaobu_b[1] * 0, yaobu_b[2] * 0);
            }
            return angle;
        }        //左侧外旋为-，内旋+， 右侧内旋为-，外旋+

        public static float reqYaobuQuShengAngleToGround(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu_b[0], yaobu_b[1]*0, yaobu_b[2]*0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0]*0, yaobu_yd[1], yaobu_yd[2]*0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            return angle;
        }  //骨盆前倾为-，后倾为+

        public static float reqNeixuanWaiXuanAngle3(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 0);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 1, 0, 0, 0, 1, 0);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0], yaobu_b[1]*0, yaobu_b[2]*0);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0] * 0, yaobu_yd[1] * 0, yaobu_yd[2]);

            float angle = 0;
            if (aaa - 90 > 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0], yaobu_b[1] * 0, yaobu_b[2] * 0);
            }
            else if (aaa - 90 <= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0], yaobu_b[1] * 0, yaobu_b[2] * 0);
            }
            return angle;
        }   //左腿内扣为-，外扣为+，右腿外-，内+, 腰部右旋顺时针+，左旋逆时针-

        public static float reqWaizhanNeishouAngleToGround3(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu[0]*0, yaobu[1], yaobu[2]*0, 0, 0, 1);
            
            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], yaobu_yd[1]*0, yaobu_yd[2]*0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            else if (aaa - 40 >= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            return angle;
        }  //骨盆左右摆动，向左-，向右+，左腿外展+，内收-，右腿外展-，内收+

        public static float reqWaizhanNeishouAngleToGround4(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu[0] * 0, yaobu[1], yaobu[2] * 0, 0, 0, 1);

            float[] yaobu_b_proj = new float[3];
            yaobu_b_proj = reqProjectionVectorToASurface(yaobu_b[0], yaobu_b[1], yaobu_b[2], yaobu[0] * 0, yaobu[1], yaobu[2] * 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], yaobu_yd[1] * 0, yaobu_yd[2] * 0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            }
            else if (aaa - 40 >= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            }
            return angle;
        }  //骨盆左右摆动，向左+，向右-，

        public static float reqWaizhanNeishouAngleToBody(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu[0] * 0, yaobu[1], yaobu[2] * 0, 0, 0, 1);
            float[] yaobu_b_proj = new float[3];
            yaobu_b_proj = reqProjectionVectorToASurface(yaobu_b[0], yaobu_b[1], yaobu_b[2], yaobu[0] * 0, yaobu[1], yaobu[2] * 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], yaobu_yd[1] * 0, yaobu_yd[2] * 0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            }
            else if (aaa - 40 >= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            }
            return angle;
        }  //左腿外展+，内收-，右腿外展-，内收+

        public static float reqNeifanWaifanAngle4(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 1, 0, 0, 0, 1, 0);

            float[] yaobu_proj = new float[3];
            yaobu_proj = reqProjectionVectorToASurface(yaobu_b[0], yaobu_b[1], yaobu_b[2], 1, 0, 0, 0, 1, 0);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0]*1, yaobu_proj[1] * 1, yaobu_proj[2] * 0);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(1, 0, 0, 0, 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0] * 0, yaobu_yd[1] * 0, yaobu_yd[2]*1);

            float angle = 0;
            if (aaa - 20 <= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0]*1, yaobu_proj[1] * 1, yaobu_proj[2] * 0);
            }
            else if (aaa - 20 > 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0]*1, yaobu_proj[1] * 1, yaobu_proj[2] * 0);
            }
            return angle;
        }   //左腿内扣为+，外扣为-，右腿外扣为+，内扣为-

        public static float reqButaineikouAngle(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);

            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu[0] * 0, yaobu[1], yaobu[2] * 0, 0, 0, 1);

            float[] yaobu_b_proj = new float[3];
            yaobu_b_proj = reqProjectionVectorToASurface(yaobu_b[0], yaobu_b[1], yaobu_b[2], yaobu[0] * 0, yaobu[1], yaobu[2] * 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], yaobu_yd[1] * 0, yaobu_yd[2] * 0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            }
            else if (aaa - 40 >= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            }
            return angle;
        }  //左腿内扣为+，外扣为-，右腿外扣为+，内扣为-

        public static float reqPaziWaizhan(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 1, 0, 0, 0, 1, 0);

            float[] yaobu_b_proj = new float[3];
            yaobu_b_proj = reqProjectionVectorToASurface(yaobu_b[0], yaobu_b[1], yaobu_b[2], 1, 0, 0, 0, 1, 0);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0] * 1, yaobu_b_proj[1] * 1, yaobu_b_proj[2] * 1);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], 0, 0, 1);

            float angle = 0;
            if (aaa - 20 <= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0] * 1, yaobu_b_proj[1] * 1, yaobu_b_proj[2] * 1);
            }
            else if (aaa - 20 > 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0] * 1, yaobu_b_proj[1] * 1, yaobu_b_proj[2] * 1);
            }
            return angle;
        }   //外展为-，内收为+

        public static float reqPaziTuibuQuShengAngleToGround(float[] float_array, int firNum, int secNum)
        {
            float angle = reqMainAngleRelative(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2, 1, 0, 0, 0, 2);
            return angle;
        }   //

        public static float reqPaziYaobuQuShengAngleToGround(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu_b[0], 0, 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], 0, yaobu_yd[1], 0);

            float angle = reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);

            return angle;
        }   //骨盆前倾为+，后倾为-

        public static float reqPaziYaobuZXuanzhuan(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 0);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 0, yaobu_b[1], 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, zuodatui[2]);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], 0, 0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, zuodatui[2]);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, zuodatui[2]);
            }
            return angle;
        }   // 顺时针（右旋）为+，逆时针（左旋）为-

        public static float reqPaziYaobuZuoyouxuanzhuan(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 1, 0, 0, 0, 1, 0);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0] * 1, 0, 0);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], 0, 0, 1);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0] * 1, 0, 0);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0] * 1, 0, 0);
            }
            return angle;
        }   //

        public static float reqPaziQuShengAngle(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);
            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu_b[0], yaobu_b[1]*0, yaobu_b[2]*0, 0, 0, 1);
            float[] yaobu_proj = new float[3];
            yaobu_proj = reqProjectionVectorToASurface(yaobu[0], yaobu[1], yaobu[2], yaobu_b[0], yaobu_b[1]*0, yaobu_b[2]*0, 0, 0, 1);
            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0], yaobu_proj[1], yaobu_proj[2]);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], yaobu_yd[1], yaobu_yd[2]);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0], yaobu_proj[1], yaobu_proj[2]);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0], yaobu_proj[1], yaobu_proj[2]);
            }
            return angle;
        }        //膝盖屈伸，+为伸，-为屈

        public static float reqPaziXiaotuidakai(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);
            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 0, yaobu[1], 0, 0, 0, 1);
            float[] yaobu_b_proj = new float[3];
            yaobu_b_proj = reqProjectionVectorToASurface(yaobu_b[0], yaobu_b[1], yaobu_b[2], 0, yaobu[1], 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], 0, 0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            }
            return angle;
        }  //趴姿大腿打开+，收拢-

        public static float reqPaziXiaotuidakaiDance(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 1);
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);
            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 0, yaobu[1], 0, 0, 0, 1);
            float[] yaobu_b_proj = new float[3];
            yaobu_b_proj = reqProjectionVectorToASurface(yaobu_b[0], yaobu_b[1], yaobu_b[2], 0, yaobu[1], 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], 0, 0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            return angle;
        }  //趴姿大腿 左侧打开-，收拢+，右侧打开+，收拢-

        public static float reqZuoziQuShengAngle(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);
            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 1, 0, 0, 0, 1, 0);
            float[] yaobu_proj = new float[3];
            yaobu_proj = reqProjectionVectorToASurface(yaobu[0], yaobu[1], yaobu[2], 1, 0, 0, 0, 1, 0);
            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0], yaobu_proj[1], yaobu_proj[2]);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], 0, 0, yaobu_yd[2]);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0], yaobu_proj[1], yaobu_proj[2]);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_proj[0], yaobu_proj[1], yaobu_proj[2]);
            }
            return angle;
        }        //膝盖屈伸，左侧-为伸，+为屈，右侧+为伸，-为屈

        public static float reqZuoziNeishou(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 1, 0, 0, 0, 1, 0);

            float[] yaobu_b_proj = new float[3];
            yaobu_b_proj = reqProjectionVectorToASurface(yaobu_b[0], yaobu_b[1], yaobu_b[2], 1, 0, 0, 0, 1, 0);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], -yaobu_b_proj[0] * 1, yaobu_b_proj[1] * 0, yaobu_b_proj[2] * 0);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], 0, 0, 1);

            float angle = 0;
            if (aaa - 20 <= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], -yaobu_b_proj[0] * 1, yaobu_b_proj[1] * 0, yaobu_b_proj[2] * 0);
            }
            else if (aaa - 20 > 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], -yaobu_b_proj[0] * 1, yaobu_b_proj[1] * 0, yaobu_b_proj[2] * 0);
            }
            return angle;
        }   //右腿内收为-，左腿内收为+

        public static float reqPaziWaizhan2(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 1, 0, 0, 0, 1, 0);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0] * 1, 0, 0);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], 0, 0, 1);

            float angle = 0;
            if (aaa - 20 <= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0] * 1, 0, 0);
            }
            else if (aaa - 20 > 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b[0] * 1, 0, 0);
            }
            return angle;
        }   //右腿外展为-，左腿外展为+

        public static float reqCechengWaizhan(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);

            float[] yaobu_b = new float[3];
            yaobu_b = reqMainAnglePosition(float_array[4 * firNum + 3], float_array[4 * firNum + 0], float_array[4 * firNum + 1], float_array[4 * firNum + 2], 2);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu[0], 0, 0, 0, 0, 1);

            float[] yaobu_b_proj = new float[3];
            yaobu_b_proj = reqProjectionVectorToASurface(yaobu_b[0], yaobu_b[1], yaobu_b[2], yaobu[0], 0, 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], 0, yaobu_yd[1], 0);

            float angle = 0;
            if (aaa - 20 <= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            }
            else if (aaa - 20 > 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu_b_proj[0], yaobu_b_proj[1], yaobu_b_proj[2]);
            }
            return angle;
        }   //两腿外展为+，内收为-

        public static float reqCechengWaizhan2(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], yaobu[0], 0, 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu[0], 0, 0);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], 0, yaobu_yd[1], 0);

            float angle = 0;
            if (aaa - 20 <= 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu[0], 0, 0);
            }
            else if (aaa - 20 > 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], yaobu[0], 0, 0);
            }
            return angle;
        }   //左侧外展为-，右侧外展为+

        public static float reqCechengYaobuZXuanzhuanLeft(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 1);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 0, yaobu[1], 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], 0, 0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            return angle;
        }   //?

        public static float reqCechengYaobuZXuanzhuanRight(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 1);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 0, yaobu[1], 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, -1);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], 0, 0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, -1);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, -1);
            }
            return angle;
        }   //?

        public static float reqZuoziJiaozhunTuichangshangAngle(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(1, 0, 0, 0, 1);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 0);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 0, yaobu[1], 0, 0, 0, 1);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(1, 0, 0, 0, 0);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], yaobu_yd[0], 0, 0);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], 0, 0, 1);
            }
            return angle;
        }   //坐姿校准腿朝上

        public static float reqZuoziJiaozhunJiaoxiangqianAngle(float[] float_array, int firNum, int secNum)
        {
            float[] yaobu = new float[3];
            yaobu = reqMainAnglePosition(1, 0, 0, 0, 0);

            float[] zuodatui = new float[3];
            zuodatui = reqMainAnglePosition(float_array[4 * secNum + 3], float_array[4 * secNum + 0], float_array[4 * secNum + 1], float_array[4 * secNum + 2], 2);

            float[] zuodatui_proj = new float[3];
            zuodatui_proj = reqProjectionVectorToASurface(zuodatui[0], zuodatui[1], zuodatui[2], 1, 0, 0, 0, 1, 0);

            float[] n_ = new float[3];
            n_ = reqNVector(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], -1, 0, 0);
            float[] yaobu_yd = new float[3];
            yaobu_yd = reqMainAnglePosition(1, 0, 0, 0, 2);
            float aaa = reqMainAngleLMNRelative(n_[0], n_[1], n_[2], 0, 0, yaobu_yd[2]);

            float angle = 0;
            if (aaa - 40 < 0)
            {
                angle = +reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], -1, 0, 0);
            }
            else if (aaa - 40 >= 0)
            {
                angle = -reqMainAngleLMNRelative(zuodatui_proj[0], zuodatui_proj[1], zuodatui_proj[2], -1, 0, 0);
            }
            return angle;
        }   //坐姿校准腿朝前

        public static float reqAccMaxTotal(float[] float_array, int secNum)
        {
            //float_array[3 * secNum + 0 + 28]
            if(Math.Abs(float_array[3 * secNum + 0 + 28]) < 16 && Math.Abs(float_array[3 * secNum + 1 + 28]) < 16 && Math.Abs(float_array[3 * secNum + 2 + 28]) < 16)
            {
                float angle = (float)Math.Sqrt(float_array[3 * secNum + 0 + 28] * float_array[3 * secNum + 0 + 28] +
                                        float_array[3 * secNum + 1 + 28] * float_array[3 * secNum + 1 + 28] +
                                        float_array[3 * secNum + 2 + 28] * float_array[3 * secNum + 2 + 28] );
                return angle;
            }
            return 0;
            
        }   //加速度计算

        public static List<double> pinhuaquxian(List<double>[,] processAngleListList, int row, int column, int pinhuaLength_need_double)
        {
            //int pinhuaLength = 26;
            int pinhuaLength = pinhuaLength_need_double;
            double[] itemDouble = new double[pinhuaLength];
            List<double> dimianjiajiao_left_pinhua = new List<double>(itemDouble);
            List<double> dimianjiajiao_left_pinhua_10_tmp = new List<double>();
            
            for (int i = 0; i < pinhuaLength; i++)
            {
                if (processAngleListList[row, column].Count() > pinhuaLength)
                {
                    dimianjiajiao_left_pinhua_10_tmp.Add(processAngleListList[row, column][i]);
                }
            }
            for (int i = pinhuaLength; i < processAngleListList[row, column].Count(); i++)
            {
                if (processAngleListList[row, column].Count() > pinhuaLength)
                {
                    //求和
                    double sum = 0;
                    for (int j = 0; j < pinhuaLength; j++)
                    {
                        sum += dimianjiajiao_left_pinhua_10_tmp[j];
                    }
                    //处理
                    dimianjiajiao_left_pinhua.Add(sum / pinhuaLength);
                    dimianjiajiao_left_pinhua_10_tmp.RemoveAt(0);
                    dimianjiajiao_left_pinhua_10_tmp.Add(processAngleListList[row, column][i]);
                }
            }
            return dimianjiajiao_left_pinhua;
        }

        public static List<int> huaxianValueDown(List<double> dimianjiajiao_left_pinhua, int limit, int pinhuaLength_need_double)
        {
            List<int> dimianjiajiao_min = new List<int>();
            double xigaiqusheng_pre = 0;
            double xigaiqusheng = dimianjiajiao_left_pinhua[0];
            double xigaiqusheng_next = dimianjiajiao_left_pinhua[1];
            for (int i = 2; i < dimianjiajiao_left_pinhua.Count(); i++)
            {
                xigaiqusheng_pre = xigaiqusheng;
                xigaiqusheng = xigaiqusheng_next;
                xigaiqusheng_next = dimianjiajiao_left_pinhua[i];
                if (xigaiqusheng < xigaiqusheng_pre && xigaiqusheng < xigaiqusheng_next && xigaiqusheng < limit)
                {
                    dimianjiajiao_min.Add(i-1- pinhuaLength_need_double/2);
                }
            }
            return dimianjiajiao_min;
        }

        public static List<int> huaxianValueUp(List<double> dimianjiajiao_left_pinhua, int limit, int pinhuaLength_need_double)
        {
            List<int> dimianjiajiao_min = new List<int>();
            double xigaiqusheng_pre = 0;
            double xigaiqusheng = dimianjiajiao_left_pinhua[0];
            double xigaiqusheng_next = dimianjiajiao_left_pinhua[1];
            for (int i = 2; i < dimianjiajiao_left_pinhua.Count(); i++)
            {
                xigaiqusheng_pre = xigaiqusheng;
                xigaiqusheng = xigaiqusheng_next;
                xigaiqusheng_next = dimianjiajiao_left_pinhua[i];
                if (xigaiqusheng > xigaiqusheng_pre && xigaiqusheng > xigaiqusheng_next && xigaiqusheng > limit)
                {
                    dimianjiajiao_min.Add(i-1- pinhuaLength_need_double/2);
                }
            }
            return dimianjiajiao_min;
        }

        public static List<int> huaxianValueDownOnlyOneTime(List<double> dimianjiajiao_left_pinhua, int limit, int huifuLimit, int pinhuaLength_need_double)
        {
            List<int> dimianjiajiao_min = new List<int>();
            double xigaiqusheng_pre = 0;
            double xigaiqusheng = dimianjiajiao_left_pinhua[0];
            double xigaiqusheng_next = dimianjiajiao_left_pinhua[1];

            int savedFlag = 0;
            for (int i = 2; i < dimianjiajiao_left_pinhua.Count(); i++)
            {
                xigaiqusheng_pre = xigaiqusheng;
                xigaiqusheng = xigaiqusheng_next;
                xigaiqusheng_next = dimianjiajiao_left_pinhua[i];
                if (xigaiqusheng < xigaiqusheng_pre && xigaiqusheng < xigaiqusheng_next && xigaiqusheng < limit && savedFlag == 0)
                {
                    dimianjiajiao_min.Add(i - 1 - pinhuaLength_need_double / 2);
                    savedFlag = 1;
                }
                if( xigaiqusheng > huifuLimit)
                {
                    savedFlag = 0;
                }
            }
            return dimianjiajiao_min;
        }

        public static List<int> huaxianValueUpOnlyOneTime(List<double> dimianjiajiao_left_pinhua, int limit, int huifuLimit, int pinhuaLength_need_double)
        {
            List<int> dimianjiajiao_min = new List<int>();
            double xigaiqusheng_pre = 0;
            double xigaiqusheng = dimianjiajiao_left_pinhua[0];
            double xigaiqusheng_next = dimianjiajiao_left_pinhua[1];

            int savedFlag = 0;
            for (int i = 2; i < dimianjiajiao_left_pinhua.Count(); i++)
            {
                xigaiqusheng_pre = xigaiqusheng;
                xigaiqusheng = xigaiqusheng_next;
                xigaiqusheng_next = dimianjiajiao_left_pinhua[i];
                if (xigaiqusheng > xigaiqusheng_pre && xigaiqusheng > xigaiqusheng_next && xigaiqusheng > limit && savedFlag == 0)
                {
                    dimianjiajiao_min.Add(i - 1 - pinhuaLength_need_double / 2);
                    savedFlag = 1;
                }
                if (xigaiqusheng < huifuLimit)
                {
                    savedFlag = 0;
                }
            }
            return dimianjiajiao_min;
        }

        public static List<int> quchong(List<int> xigaishuzhi_right)
        {
            List<int> xigaishuzhi_right_tmp = new List<int>();
            if (xigaishuzhi_right.Count() == 0){
                return xigaishuzhi_right_tmp;
            }
            
            xigaishuzhi_right_tmp.Add(xigaishuzhi_right[0]);
            for (int i = 1; i < xigaishuzhi_right.Count(); i++)
            {
                int item = xigaishuzhi_right[i];
                int count = 0;
                for (int j = 0; j < xigaishuzhi_right_tmp.Count(); j++)
                {
                    if (xigaishuzhi_right_tmp[j] == item)
                    {
                        count++;
                    }
                }
                if (count == 0)
                {
                    xigaishuzhi_right_tmp.Add(item);
                }
            }
            return xigaishuzhi_right_tmp;
        }

        public static int countInRange(List<int> dimianjiajiao_min_right, int timeStart, int timeStop, int range_up, int range_down)
        {
            int countTmp = 0;
            for (int j = 0; j < dimianjiajiao_min_right.Count(); j++)
            {
                if (dimianjiajiao_min_right[j] <= timeStop + range_up && dimianjiajiao_min_right[j] >= timeStart - range_down)
                {
                    countTmp++;
                }
            }
            return countTmp;
        }

        public static float[] reqAccToDistance(float[] float_array, int secNum, float velocity, float juli, int oldTime, int newTime)
        {
            //float_array[3 * secNum + 0 + 28]
            float[] ret = new float[3];

            float acc = (float)Math.Sqrt(float_array[3 * secNum + 0 + 28] * float_array[3 * secNum + 0 + 28] +
                                        float_array[3 * secNum + 1 + 28] * float_array[3 * secNum + 1 + 28] +
                                        float_array[3 * secNum + 2 + 28] * float_array[3 * secNum + 2 + 28]) - 1F;

            if(oldTime <= 0)
            {
                velocity = 0;
                juli = 0;
                ret[0] = velocity;
                ret[1] = juli;
                ret[2] = newTime;

                return ret;
            }

            if ((acc > 0.20 || acc < -0.1) && (newTime - oldTime > 0) && Math.Abs(acc) < 16)
            {
                velocity = velocity + Math.Abs(acc) * ((float)(newTime - oldTime)) * 0.01F;
            }

            if(newTime - oldTime > 0)
            {
                juli = juli + velocity * ((float)(newTime - oldTime)) * 0.01F;
            }
              
            ret[0] = velocity;
            ret[1] = juli;
            ret[2] = newTime;

            return ret;

        }   //加速度计算

        //求随机数平均值方法
        public static double Ave(double[] a)
        {
            double sum = 0;
            foreach (double d in a)
            {

                sum = sum + d;
            }
            double ave = sum / a.Length;

            return ave;
        }
        //求随机数方差方法
        public static double Var(double[] v)
        {
            //    double tt = 2;
            //double mm = tt ^ 2;

            double sum1 = 0;
            for (int i = 0; i < v.Length; i++)
            {
                double temp = v[i] * v[i];
                sum1 = sum1 + temp;

            }

            double sum = 0;
            foreach (double d in v)
            {
                sum = sum + d;
            }

            double var = sum1 / v.Length - (sum / v.Length) * (sum / v.Length);
            return var;
        }


        public static string prinfFloat(double[] f)
        {
            string stableStateString = "";
            for (int i = 0; i < f.Length; i++)
            {
               stableStateString += f[i] + ",";
            }
            return stableStateString;
        }

        public static void printList(List<int> dimianjiajiao_min_left, string str)
        {
            string xxxx = "";
            xxxx += str + ": ";
            for (int i = 0; i < dimianjiajiao_min_left.Count(); i++)
            {
                xxxx += dimianjiajiao_min_left[i] + ", ";
            }
            Console.WriteLine(xxxx);
        }

        public static void printListDouble(List<double> dimianjiajiao_min_left, string str)
        {
            string xxxx = "";
            xxxx += str + ": ";
            for (int i = 0; i < dimianjiajiao_min_left.Count(); i++)
            {
                xxxx += dimianjiajiao_min_left[i] + ", ";
            }
            Console.WriteLine(xxxx);
        }

        //综合计算一段的最大值，最小值，平均值，方差
        public static double[] calMaxMinMeanVar(List<double> processAngleListList, int timeStart, int timeStop)
        {
            List<double> valueInRange = new List<double>();
            double[] ret = new double[4];
            double maxValue = -10000;
            double minValue = 10000;
            double meanValue = 0;
            double varValue = 0;
            for (int j = timeStart; j <= timeStop; j++)
            {
                double value = processAngleListList[j];
                valueInRange.Add(value);
                if (value > maxValue)
                {
                    maxValue = value;
                }
                if (value < minValue)
                {
                    minValue = value;
                }
            }
            meanValue = HermesCalculator.Ave(valueInRange.ToArray());
            varValue = HermesCalculator.Var(valueInRange.ToArray());
            //string str = "";
            //str += "足过度外翻-右 最大值：" + maxValue + " 最小值：" + minValue + " 平均值：" + meanValue + " 方差：" + varValue;
            //Console.WriteLine(str);
            ret[0] = maxValue; ret[1] = minValue; ret[2] = meanValue; ret[3] = varValue;
            return ret;
        }


    }    //角度计算器

    public class HermesStateStablization
    {
        //预计稳定的值
        public float[] stablizedVariable = new float[20];
        //需要稳定的数量
        public int numOfVariable;
        //稳定前的值
        public float[] preVariable = new float[20];
        //稳定期望的值
        public float[] expectedVariable = new float[20];
        //稳定期望的上限
        public float[] expectedUp = new float[20];
        //稳定期望的下限
        public float[] expectedDown = new float[20];
        ////前5个点的值
        //public List<float[]> pre5AngleList;
        ////前5个点的和
        //public float[] pre5AngleSum = new float[20];
        //是否进入稳定阶段
        public int isStable;
        //稳定阶段的上限
        public float[] stableUp = new float[20];
        //稳定阶段的下限
        public float[] stableDown = new float[20];
        //是否为上升阶段
        public int[] isUpStage = new int[20];
        //是否为下降阶段
        public int[] isDownStage = new int[20];
        //稳定时间
        public int stableTime;
        //是否是期望区间
        public int m_isAllInExpectedArea;
        //是否是稳定区间
        public int m_isAllInStableArea;

        //初始化函数
        public HermesStateStablization()
        {
            numOfVariable = 0;
        }

        //重置函数
        public void reset(float[] preVariable_, float[] expectedVariable_, float[] expectedUp_, float[] expectedDown_, float[] stableUp_, float[] stableDown_,
                                        int numOfVariable_)
        {
            numOfVariable = numOfVariable_;
            for (int i = 0; i < numOfVariable_; i++)
            {
                preVariable[i] = preVariable_[i];
                expectedVariable[i] = expectedVariable_[i];
                expectedUp[i] = expectedUp_[i];
                expectedDown[i] = expectedDown_[i];
                stableUp[i] = stableUp_[i];
                stableDown[i] = stableDown_[i];
                stablizedVariable[i] = 0;
                isUpStage[i] = 0;
                isDownStage[i] = 0;
            }

            //pre5AngleList.Clear();
            isStable = 0;
            stableTime = 0;
            m_isAllInExpectedArea = 0;
            m_isAllInStableArea = 0;
            isStable = 0;
        }

        //稳定状态,只要稳定了，并且在期望区间内，就算是稳定了
        public int stableState(float[] variable, int duration)
        {
            int ret = 1;
            //尝判断是否是期望区间
            int isAllInExpectedArea = 1;
            for (int i = 0; i < numOfVariable; i++)
            {
                if(variable[i] <= (expectedVariable[i] + expectedUp[i]) && variable[i] >= (expectedVariable[i] - expectedDown[i]))
                {
                    //该变量在期望区间内
                }
                else
                {
                    isAllInExpectedArea = 0;
                }
            }
            //尝判断是否是稳定区间
            int isAllInStableArea = 1;
            for (int i = 0; i < numOfVariable; i++)
            {
                if (variable[i] > (stablizedVariable[i] + stableUp[i]) || variable[i] < (stablizedVariable[i] - stableDown[i]))
                {
                    //该变量不在稳定区间
                    isAllInStableArea = 0;
                }
                else
                {

                }
            }
            m_isAllInExpectedArea = isAllInExpectedArea;
            m_isAllInStableArea = isAllInStableArea;

            if (isStable == 0)    //未稳定，尝试进入稳定，或者判断是上升还是下降
            {
                
                if(isAllInStableArea == 1)
                {
                    //如果在稳定区间
                    //消除上升或者下降
                    for (int i = 0; i < numOfVariable; i++)
                    {
                        //判断认为是上升或者下降的
                        for (int j = 0; j < numOfVariable; j++)
                        {
                            if (variable[j] > stablizedVariable[j])
                            {
                                isUpStage[j] = 1;
                                isDownStage[j] = 0;
                            }
                            else if (variable[j] < stablizedVariable[j])
                            {
                                isDownStage[j] = 1;
                                isUpStage[j] = 0;
                            }
                        }
                    }
                    if (isAllInExpectedArea == 1)  //在期望区间内
                    {
                        //变量在稳定区间,开始计时
                        isStable = 1;
                        stableTime = 0;
                    }else if(isAllInExpectedArea == 0)   //不在期望区间内
                    {
                        //没有意义的稳定
                        isStable = 1;
                        stableTime = 0;
                    }
                }
                else if(isAllInStableArea == 0)
                {
                    //变量不在稳定区间，判断上升还是下降
                    isStable = 0;
                    stableTime = 0;
                    for (int i = 0; i < numOfVariable; i++)
                    {
                        if(variable[i] > stablizedVariable[i] + stableUp[i])
                        {
                            isUpStage[i] = 1;
                            isDownStage[i] = 0;
                        }
                        else if(variable[i] < stablizedVariable[i] + stableUp[i])
                        {
                            isDownStage[i] = 1;
                            isUpStage[i] = 0;
                        }
                    }
                    //修改稳定值
                    for (int i = 0; i < numOfVariable; i++)
                    {
                        stablizedVariable[i] = variable[i];
                    }
                }
            }
            else if(isStable == 1)    //进入稳定区间，或者跳出稳定区间
            {
                if (isAllInStableArea == 1)
                {
                    //如果在稳定区间
                    //消除上升或者下降
                    if(stableTime <= 1)
                    {
                        //1次计数还是认为是上升或者下降的
                        for (int j = 0; j < numOfVariable; j++)
                        {
                            if (variable[j] > stablizedVariable[j])
                            {
                                isUpStage[j] = 1;
                                isDownStage[j] = 0;
                            }
                            else if (variable[j] < stablizedVariable[j])
                            {
                                isDownStage[j] = 1;
                                isUpStage[j] = 0;
                            }
                        }
                    }
                    else
                    {
                        for (int i = 0; i < numOfVariable; i++)
                        {
                            isUpStage[i] = 0;
                            isDownStage[i] = 0;
                        }
                    }
                    if (isAllInExpectedArea == 1)  //在期望区间内
                    {
                        //变量在稳定区间,开始计时
                        isStable = 1;
                        stableTime ++;
                    }
                    else if (isAllInExpectedArea == 0)   //不在期望区间内
                    {
                        //没有意义的稳定
                        isStable = 1;
                        stableTime++;
                    }
                }
                else if (isAllInStableArea == 0)
                {
                    //变量不在稳定区间，判断上升还是下降
                    isStable = 0;
                    stableTime = 0;
                    for (int i = 0; i < numOfVariable; i++)
                    {
                        if (variable[i] > stablizedVariable[i] + stableUp[i])
                        {
                            isUpStage[i] = 1;
                            isDownStage[i] = 0;
                        }
                        else if (variable[i] < stablizedVariable[i] + stableUp[i])
                        {
                            isDownStage[i] = 1;
                            isUpStage[i] = 0;
                        }
                    }
                    //修改稳定值
                    for (int i = 0; i < numOfVariable; i++)
                    {
                        stablizedVariable[i] = variable[i];
                    }
                }
            }

            ////初始化求和
            //for (int i = 0; i < numOfVariable; i++)
            //{
            //    pre5AngleSum[i] = 0;
            //}
            
            ////计算前5个值的平均值
            //if(pre5AngleList.Count() >= 5)
            //{
            //    //求和
            //    for (int i = 0; i < numOfVariable; i++)
            //    {
            //        for (int j = 0; j < 5; j++)
            //        {
            //            pre5AngleSum[i] += pre5AngleList[j][i];
            //        }
            //    }

            //    //求平均
                
            //}
            //else
            //{
            //    pre5AngleList.Add(variable);
            //    ret = 0;
            //}
            return ret;
        }

    }    //状态稳定器，储存最近一段时间的状态

    public class HermesStateDetctor
    {
        //进度条(0-1) float
        public float m_jindutiao;
        //开始计时/结束计时（0/1）int
        public int m_jishi;
        //计时时间 float
        public int m_timeDuration;
        //阶段提示 （0/1）int
        public int m_tipFlag;
        //阶段提示内容 string
        public string m_tipContent;
        //准备阶段是否采集成功（0/1）int
        public int m_prepFlag;
        //动作成功与否（-1/0/1）int
        public int m_successFlag;
        //当前角度
        public float[] m_variable_ = new float[30];

        //初始化函数
        public HermesStateDetctor()
        {

        }

        public virtual void reset()
        {

        }

        public void resetTipFlag()
        {
            m_tipFlag = 0;
            m_tipContent = "";
        }

        //准备阶段状态处理器
        public virtual void calcPrep(float[] float_array, int lineIndex)
        {

        }

        //状态处理器
        public virtual void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            
        }

        //获得特征
        public virtual Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            return ret;
        }


    }  //状态检测器-通用类-基类

    public class HermesStateDetctorForZuoCeDanTuiQuKuanShenXi : HermesStateDetctor
    {

        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 3;
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum,10];

        //初始化函数
        public HermesStateDetctorForZuoCeDanTuiQuKuanShenXi()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            //准备阶段稳定器
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0};
            float[] expectedUp_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] expectedDown_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] stableUp_ = new float[] { 3, 3, 3, 3, 3, 3 };
            float[] stableDown_ = new float[] { 3, 3, 3, 3, 3, 3 };
            int numOfVariable_ = 6;
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1
            preVariable_ = new float[] { 0 };
            expectedVariable_ = new float[] { 90 };
            expectedUp_ = new float[] { 50 };
            expectedDown_ = new float[] { 15 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器2
            preVariable_ = new float[] { 0 };
            expectedVariable_ = new float[] { 0 };
            expectedUp_ = new float[] { 25 };
            expectedDown_ = new float[] { 20 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;
            m_hermesStateStablization_List[2] = new HermesStateStablization();
            m_hermesStateStablization_List[2].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i,j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            //准备阶段稳定器
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedUp_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] expectedDown_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] stableUp_ = new float[] { 3, 3, 3, 3, 3, 3 };
            float[] stableDown_ = new float[] { 3, 3, 3, 3, 3, 3 };
            int numOfVariable_ = 6;
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1
            preVariable_ = new float[] { 0 };
            expectedVariable_ = new float[] { 90 };
            expectedUp_ = new float[] { 50 };
            expectedDown_ = new float[] { 20 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器2
            preVariable_ = new float[] { 0 };
            expectedVariable_ = new float[] { 0 };
            expectedUp_ = new float[] { 40 };
            expectedDown_ = new float[] { 30 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;
            m_hermesStateStablization_List[2] = new HermesStateStablization();
            m_hermesStateStablization_List[2].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器
                float[] variable_ = new float[] { 0, 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1);
                variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 0, 2);
                variable_[2] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                variable_[3] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                variable_[4] = HermesCalculator.reqQuShengAngle(float_array, 3, 5);
                variable_[5] = HermesCalculator.reqQuShengAngle(float_array, 4, 6);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState+1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1 
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    
                    Console.WriteLine("准备阶段采集完成！");
                    m_tipFlag = 1;
                    m_tipContent = "准备阶段采集完成！";
                    m_prepFlag = 1;
                    m_jindutiao = 0;
                    return;
                }
                else if(m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if(m_currentState == 0)     
            {
                //状态1的通过稳定器
                float[] variable_ = new float[] { 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1 
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    } 
                    Console.WriteLine("第一阶段采集完成！");
                    m_tipFlag = 1;
                    m_tipContent = "第一阶段采集完成！";

                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                    if(m_hermesStateStablization_List[m_currentState + 1].isUpStage[0] == 1)
                    {
                        //上升情况 - 腰部角度变化 + 支撑脚角度变化
                        //腰部前后倾
                        float yaobu_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 0].Add(yaobu_x);
                        //腰部旋转
                        float yaobu_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 2].Add(yaobu_z);
                        //左右摆动，向左-，向右+
                        float yaobu_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 1].Add(yaobu_y);
                        //右脚部前后倾
                        float jiao_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 6, 6);
                        processAngleListList[m_currentState + 1, 3].Add(jiao_x);
                        //右脚部旋转
                        float jiao_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 6, 6);
                        processAngleListList[m_currentState + 1, 5].Add(jiao_z);
                        //右脚部左右摆动，向左-，向右+
                        float jiao_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 6, 6);
                        processAngleListList[m_currentState + 1, 4].Add(jiao_y);
                        //角度
                        float angle = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                        processAngleListList[m_currentState + 1, 6].Add(angle);
                    }
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1) ) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1) )
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //状态2触发条件函数
        public void state2StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 1)
            {
                //状态1的通过稳定器
                float[] variable_ = new float[] { 0 };
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "2是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过100*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1 
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 2;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第二状态采集完成！");
                    m_tipFlag = 1;
                    m_tipContent = "第二阶段采集完成！";
                    m_successFlag = 1;
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                    if (m_hermesStateStablization_List[m_currentState + 1].isDownStage[0] == 1)
                    {
                        //下降情况 - 腰部角度变化 + 支撑脚角度变化
                        //腰部前后倾
                        float yaobu_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 0].Add(yaobu_x);
                        //腰部旋转
                        float yaobu_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 2].Add(yaobu_z);
                        //左右摆动，向左-，向右+
                        float yaobu_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 1].Add(yaobu_y);
                        //右脚部前后倾
                        float jiao_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 6, 6);
                        processAngleListList[m_currentState + 1, 3].Add(jiao_x);
                        //右脚部旋转
                        float jiao_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 6, 6);
                        processAngleListList[m_currentState + 1, 5].Add(jiao_z);
                        //右脚部左右摆动，向左-，向右+
                        float jiao_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 6, 6);
                        processAngleListList[m_currentState + 1, 4].Add(jiao_y);
                        //角度
                        float angle = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                        processAngleListList[m_currentState + 1, 6].Add(angle);
                    }
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 50);
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 50);
            }
            else if(m_currentState == 1 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state2StartGate(float_array, lineIndex, 100);
            }
            else if (m_currentState == 2)
            {
                //if(lineIndex % 500 == 0)
                //{
                //    reset();
                //}
            }

            if(lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                m_successFlag = -1;
                if (lineIndex % 500 == 0)
                {
                    reset();
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            //左侧伸膝不足
            ret.Add("3003", HermesCalculator.reqQuShengAngle(stageEndStateList[2], 1, 3));
            //左侧屈髋不足，大腿掉落
            ret.Add("2007", HermesCalculator.reqQuShengAngle(stageEndStateList[2], 0, 1));
            //左侧动作，站立不稳晃动

            //第一阶段腰部前后倾
            double yaobu_x_ave1 = HermesCalculator.Ave(processAngleListList[1, 0].ToArray());
            double yaobu_x_var1 = HermesCalculator.Var(processAngleListList[1, 0].ToArray());
            //第一阶段腰部旋转
            double yaobu_z_ave1 = HermesCalculator.Ave(processAngleListList[1, 2].ToArray());
            double yaobu_z_var1 = HermesCalculator.Var(processAngleListList[1, 2].ToArray());
            //第一阶段左右摆动，向左-，向右+
            double yaobu_y_ave1 = HermesCalculator.Ave(processAngleListList[1, 1].ToArray());
            double yaobu_y_var1 = HermesCalculator.Var(processAngleListList[1, 1].ToArray());
            //第一阶段右脚部前后倾
            double jiao_x_ave1 = HermesCalculator.Ave(processAngleListList[1, 3].ToArray());
            double jiao_x_var1 = HermesCalculator.Var(processAngleListList[1, 3].ToArray());
            //第一阶段右脚部旋转
            double jiao_z_ave1 = HermesCalculator.Ave(processAngleListList[1, 5].ToArray());
            double jiao_z_var1 = HermesCalculator.Var(processAngleListList[1, 5].ToArray());
            //第一阶段右脚部左右摆动，向左-，向右+
            double jiao_y_ave1 = HermesCalculator.Ave(processAngleListList[1, 4].ToArray());
            double jiao_y_var1 = HermesCalculator.Var(processAngleListList[1, 4].ToArray());

            //第二阶段腰部前后倾
            double yaobu_x_ave2 = HermesCalculator.Ave(processAngleListList[2, 0].ToArray());
            double yaobu_x_var2 = HermesCalculator.Var(processAngleListList[2, 0].ToArray());
            //第二阶段腰部旋转
            double yaobu_z_ave2 = HermesCalculator.Ave(processAngleListList[2, 2].ToArray());
            double yaobu_z_var2 = HermesCalculator.Var(processAngleListList[2, 2].ToArray());
            //第二阶段左右摆动，向左-，向右+
            double yaobu_y_ave2 = HermesCalculator.Ave(processAngleListList[2, 1].ToArray());
            double yaobu_y_var2 = HermesCalculator.Var(processAngleListList[2, 1].ToArray());
            //第二阶段右脚部前后倾
            double jiao_x_ave2 = HermesCalculator.Ave(processAngleListList[2, 3].ToArray());
            double jiao_x_var2 = HermesCalculator.Var(processAngleListList[2, 3].ToArray());
            //第二阶段右脚部旋转
            double jiao_z_ave2 = HermesCalculator.Ave(processAngleListList[2, 5].ToArray());
            double jiao_z_var2 = HermesCalculator.Var(processAngleListList[2, 5].ToArray());
            //第二阶段右脚部左右摆动，向左-，向右+
            double jiao_y_ave2 = HermesCalculator.Ave(processAngleListList[2, 4].ToArray());
            double jiao_y_var2 = HermesCalculator.Var(processAngleListList[2, 4].ToArray());

            double[] angleList = new double[] { jiao_x_var1, jiao_y_var1 , jiao_z_var1 , yaobu_x_var2 , yaobu_z_var2 , yaobu_y_var2 , jiao_x_var2 , jiao_z_var2 , jiao_y_var2 };

            double maxAngle = 0;
            for (int i = 0; i < angleList.Length; i++)
            {
                if(angleList[i] > maxAngle)
                {
                    maxAngle = angleList[i];
                }
            }

            //string stableStateString = "";
            //stableStateString += " yaobu_x_ave1：" + yaobu_x_ave1 + " yaobu_x_var1：" + yaobu_x_var1 + "\n" + 
            //                     HermesCalculator.prinfFloat(processAngleListList[1, 0].ToArray()) + "\n" +
            //                     " yaobu_y_ave1：" + yaobu_y_ave1 + " yaobu_y_var1：" + yaobu_y_var1 + "\n" +
            //                     HermesCalculator.prinfFloat(processAngleListList[1, 1].ToArray()) + "\n" +
            //                     " yaobu_z_ave1：" + yaobu_z_ave1 + " yaobu_z_var1：" + yaobu_z_var1 + "\n" +
            //                     HermesCalculator.prinfFloat(processAngleListList[1, 6].ToArray()) + "\n" +


            //                     " jiao_x_ave1：" + jiao_x_ave1 + " jiao_x_var1：" + jiao_x_var1 + "\n" +
            //                     " jiao_y_ave1：" + jiao_y_ave1 + " jiao_y_var1：" + jiao_y_var1 + "\n" +
            //                     " jiao_z_ave1：" + jiao_z_ave1 + " jiao_z_var1：" + jiao_z_var1 + "\n" +

            //                     " yaobu_x_ave2：" + yaobu_x_ave2 + " yaobu_x_var2：" + yaobu_x_var2 + "\n" +
            //                     " yaobu_y_ave2：" + yaobu_y_ave2 + " yaobu_y_var2：" + yaobu_y_var2 + "\n" +
            //                     " yaobu_z_ave2：" + yaobu_z_ave2 + " yaobu_z_var2：" + yaobu_z_var2 + "\n" +

            //                     " jiao_x_ave2：" + jiao_x_ave2 + " jiao_x_var2：" + jiao_x_var2 + "\n" +
            //                     " jiao_y_ave2：" + jiao_y_ave2 + " jiao_y_var2：" + jiao_y_var2 + "\n" +
            //                     " jiao_z_ave2：" + jiao_z_ave2 + " jiao_z_var2：" + jiao_z_var2;
            //Console.WriteLine(stableStateString);
            
            ret.Add("6001", (float)maxAngle);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoCeDanTuiQuKuanShenXi") == true)
            {
                HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiQuKuanShenXi"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ZuoCeDanTuiQuKuanShenXi", ret);
            }

            return ret;
        }


    }  //状态检测器-屈髋伸膝左

    public class HermesStateDetctorForYouCeDanTuiQuKuanShenXi : HermesStateDetctor
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 3;                                                                                      //需要改
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        //初始化函数
        public HermesStateDetctorForYouCeDanTuiQuKuanShenXi()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            //准备阶段稳定器                                                                                     //需要改
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedUp_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] expectedDown_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] stableUp_ = new float[] { 3, 3, 3, 3, 3, 3 };
            float[] stableDown_ = new float[] { 3, 3, 3, 3, 3, 3 };
            int numOfVariable_ = 6;
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改
            preVariable_ = new float[] { 0 };
            expectedVariable_ = new float[] { 90 };
            expectedUp_ = new float[] { 50 };
            expectedDown_ = new float[] { 15 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器2                                                                                     //需要改
            preVariable_ = new float[] { 0 };
            expectedVariable_ = new float[] { 0 };
            expectedUp_ = new float[] { 25 };
            expectedDown_ = new float[] { 20 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;
            m_hermesStateStablization_List[2] = new HermesStateStablization();
            m_hermesStateStablization_List[2].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            //准备阶段稳定器                                                                                     //需要改
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedUp_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] expectedDown_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] stableUp_ = new float[] { 3, 3, 3, 3, 3, 3 };
            float[] stableDown_ = new float[] { 3, 3, 3, 3, 3, 3 };
            int numOfVariable_ = 6;
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改
            preVariable_ = new float[] { 0 };
            expectedVariable_ = new float[] { 90 };
            expectedUp_ = new float[] { 50 };
            expectedDown_ = new float[] { 20 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器2                                                                                     //需要改
            preVariable_ = new float[] { 0 };
            expectedVariable_ = new float[] { 0 };
            expectedUp_ = new float[] { 40 };
            expectedDown_ = new float[] { 30 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;
            m_hermesStateStablization_List[2] = new HermesStateStablization();
            m_hermesStateStablization_List[2].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改
                float[] variable_ = new float[] { 0, 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1);
                variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 0, 2);
                variable_[2] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                variable_[3] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                variable_[4] = HermesCalculator.reqQuShengAngle(float_array, 3, 5);
                variable_[5] = HermesCalculator.reqQuShengAngle(float_array, 4, 6);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！");                                                                                     //需要改
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "准备阶段采集完成！";                                                                                     //需要改
                    m_prepFlag = 1;                                                                                     //需要改
                    m_jindutiao = 0;                                                                                     //需要改
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改
                float[] variable_ = new float[] { 0 };                                                                                     //需要改
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);    //需要改
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "第一阶段采集完成！";                                                                                     //需要改

                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                    if (m_hermesStateStablization_List[m_currentState + 1].isUpStage[0] == 1)                                                                                     //需要改
                    {
                        //上升情况 - 腰部角度变化 + 支撑脚角度变化
                        //腰部前后倾
                        float yaobu_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 0].Add(yaobu_x);
                        //腰部旋转
                        float yaobu_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 2].Add(yaobu_z);
                        //左右摆动，向左-，向右+
                        float yaobu_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 1].Add(yaobu_y);
                        //左脚部前后倾
                        float jiao_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 5, 5);
                        processAngleListList[m_currentState + 1, 3].Add(jiao_x);
                        //左脚部旋转
                        float jiao_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 5, 5);
                        processAngleListList[m_currentState + 1, 5].Add(jiao_z);
                        //左脚部左右摆动，向左-，向右+
                        float jiao_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 5, 5);
                        processAngleListList[m_currentState + 1, 4].Add(jiao_y);
                        //角度
                        float angle = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                        processAngleListList[m_currentState + 1, 6].Add(angle);
                    }
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //状态2触发条件函数
        public void state2StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 1)
            {
                //状态1的通过稳定器
                float[] variable_ = new float[] { 0 };                                                                                     //需要改
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);                                                                                     //需要改
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime); 

                //string stableStateString = "";
                //stableStateString += "2是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过100*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 2;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第二状态采集完成！");                                                                                     //需要改
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "第二阶段采集完成！";                                                                                     //需要改
                    m_successFlag = 1;                                                                                     //需要改
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                    if (m_hermesStateStablization_List[m_currentState + 1].isDownStage[0] == 1)                                                                                     //需要改
                    {
                        //下降情况 - 腰部角度变化 + 支撑脚角度变化                                                                                     //需要改
                        //腰部前后倾
                        float yaobu_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 0].Add(yaobu_x);
                        //腰部旋转
                        float yaobu_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 2].Add(yaobu_z);
                        //左右摆动，向左-，向右+
                        float yaobu_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 1].Add(yaobu_y);
                        //左脚部前后倾
                        float jiao_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 5, 5);
                        processAngleListList[m_currentState + 1, 3].Add(jiao_x);
                        //左脚部旋转
                        float jiao_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 5, 5);
                        processAngleListList[m_currentState + 1, 5].Add(jiao_z);
                        //左脚部左右摆动，向左-，向右+
                        float jiao_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 5, 5);
                        processAngleListList[m_currentState + 1, 4].Add(jiao_y);
                        //角度
                        float angle = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                        processAngleListList[m_currentState + 1, 6].Add(angle);
                    }
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 50);                                                                                     //需要改
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 50);                                                                                     //需要改
            }
            else if (m_currentState == 1 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state2StartGate(float_array, lineIndex, 100);                                                                                     //需要改
            }
            else if (m_currentState == 2)
            {
                //if (lineIndex % 500 == 0)
                //{
                //    reset();
                //}
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                m_successFlag = -1;
                if (lineIndex % 500 == 0)
                {
                    reset();
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            //左侧伸膝不足
            ret.Add("3003", HermesCalculator.reqQuShengAngle(stageEndStateList[2], 2, 4));
            //左侧屈髋不足，大腿掉落
            ret.Add("2007", HermesCalculator.reqQuShengAngle(stageEndStateList[2], 0, 2));
            //左侧动作，站立不稳晃动

            //第一阶段腰部前后倾
            double yaobu_x_ave1 = HermesCalculator.Ave(processAngleListList[1, 0].ToArray());
            double yaobu_x_var1 = HermesCalculator.Var(processAngleListList[1, 0].ToArray());
            //第一阶段腰部旋转
            double yaobu_z_ave1 = HermesCalculator.Ave(processAngleListList[1, 2].ToArray());
            double yaobu_z_var1 = HermesCalculator.Var(processAngleListList[1, 2].ToArray());
            //第一阶段左右摆动，向左-，向右+
            double yaobu_y_ave1 = HermesCalculator.Ave(processAngleListList[1, 1].ToArray());
            double yaobu_y_var1 = HermesCalculator.Var(processAngleListList[1, 1].ToArray());
            //第一阶段左脚部前后倾
            double jiao_x_ave1 = HermesCalculator.Ave(processAngleListList[1, 3].ToArray());
            double jiao_x_var1 = HermesCalculator.Var(processAngleListList[1, 3].ToArray());
            //第一阶段左脚部旋转
            double jiao_z_ave1 = HermesCalculator.Ave(processAngleListList[1, 5].ToArray());
            double jiao_z_var1 = HermesCalculator.Var(processAngleListList[1, 5].ToArray());
            //第一阶段左脚部左右摆动，向左-，向右+
            double jiao_y_ave1 = HermesCalculator.Ave(processAngleListList[1, 4].ToArray());
            double jiao_y_var1 = HermesCalculator.Var(processAngleListList[1, 4].ToArray());

            //第二阶段腰部前后倾
            double yaobu_x_ave2 = HermesCalculator.Ave(processAngleListList[2, 0].ToArray());
            double yaobu_x_var2 = HermesCalculator.Var(processAngleListList[2, 0].ToArray());
            //第二阶段腰部旋转
            double yaobu_z_ave2 = HermesCalculator.Ave(processAngleListList[2, 2].ToArray());
            double yaobu_z_var2 = HermesCalculator.Var(processAngleListList[2, 2].ToArray());
            //第二阶段左右摆动，向左-，向右+
            double yaobu_y_ave2 = HermesCalculator.Ave(processAngleListList[2, 1].ToArray());
            double yaobu_y_var2 = HermesCalculator.Var(processAngleListList[2, 1].ToArray());
            //第二阶段左脚部前后倾
            double jiao_x_ave2 = HermesCalculator.Ave(processAngleListList[2, 3].ToArray());
            double jiao_x_var2 = HermesCalculator.Var(processAngleListList[2, 3].ToArray());
            //第二阶段左脚部旋转
            double jiao_z_ave2 = HermesCalculator.Ave(processAngleListList[2, 5].ToArray());
            double jiao_z_var2 = HermesCalculator.Var(processAngleListList[2, 5].ToArray());
            //第二阶段左脚部左右摆动，向左-，向右+
            double jiao_y_ave2 = HermesCalculator.Ave(processAngleListList[2, 4].ToArray());
            double jiao_y_var2 = HermesCalculator.Var(processAngleListList[2, 4].ToArray());

            double[] angleList = new double[] { jiao_x_var1, jiao_y_var1, jiao_z_var1, yaobu_x_var2, yaobu_z_var2, yaobu_y_var2, jiao_x_var2, jiao_z_var2, jiao_y_var2 };

            double maxAngle = 0;
            for (int i = 0; i < angleList.Length; i++)
            {
                if (angleList[i] > maxAngle)
                {
                    maxAngle = angleList[i];
                }
            }
            ret.Add("6001", (float)maxAngle);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("YouCeDanTuiQuKuanShenXi") == true)
            {
                HermesNewTest.m_tezhengDic_all["YouCeDanTuiQuKuanShenXi"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("YouCeDanTuiQuKuanShenXi", ret);
            }

            return ret;
        }


    }  //状态检测器-屈髋伸膝右

    public class HermesStateDetctorForShenDun : HermesStateDetctor     //状态检测器-深蹲
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改-
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        //初始化函数
        public HermesStateDetctorForShenDun()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            //准备阶段稳定器                                                                                     //需要改-
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedUp_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] expectedDown_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] stableUp_ = new float[] { 3, 3, 3, 3, 3, 3 };
            float[] stableDown_ = new float[] { 3, 3, 3, 3, 3, 3 };
            int numOfVariable_ = 6;
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改-
            preVariable_ = new float[] { 0, 0 };
            expectedVariable_ = new float[] { -90, -90 };
            expectedUp_ = new float[] { 35, 35 };
            expectedDown_ = new float[] { 80, 80 };
            stableUp_ = new float[] { 3, 3 };
            stableDown_ = new float[] { 3, 3 };
            numOfVariable_ = 2;
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1);
                variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 0, 2);
                variable_[2] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                variable_[3] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                variable_[4] = HermesCalculator.reqQuShengAngle(float_array, 3, 5);
                variable_[5] = HermesCalculator.reqQuShengAngle(float_array, 4, 6);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    if (lineIndex <= 0 || lineIndex >= 15 * 60 * 60 * 100)
                    {
                        Console.WriteLine("准备阶段采集失败！");                                                                                     //需要改---
                        m_tipFlag = 1;                                                                                     //需要改---
                        m_tipContent = "准备阶段采集失败！";                                                                                     //需要改---
                        m_prepFlag = -1;                                                                                     //需要改---
                        m_jindutiao = 0;                                                                                     //需要改---
                        return;
                    }

                    Console.WriteLine("准备阶段采集完成！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "准备阶段采集完成！";                                                                                     //需要改-
                    m_prepFlag = 1;                                                                                     //需要改-
                    m_jindutiao = 0;                                                                                     //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0 };                                                                                     //需要改-
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);    //需要改-
                variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);    //需要改-
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改-
                    m_successFlag = 1;                                                                                      //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime && 
                         m_hermesStateStablization_List[m_currentState + 1].isDownStage[0] == 1 &&
                         m_hermesStateStablization_List[m_currentState + 1].isDownStage[1] == 1 && 
                         m_hermesStateStablization_List[m_currentState + 1].stablizedVariable[0] < -50 &&
                         m_hermesStateStablization_List[m_currentState + 1].stablizedVariable[1] < -50)
                {
                    //过程分析                                                                                                                      //需要改-
                    //任何时刻
                    //膝内扣角度 - 左
                    float angle = HermesCalculator.reqNeifanWaifanAngle4(float_array, 5, 3);
                    processAngleListList[m_currentState + 1, 0].Add(angle);
                    //膝内扣角度 - 右
                    angle = HermesCalculator.reqNeifanWaifanAngle4(float_array, 6, 4);
                    processAngleListList[m_currentState + 1, 1].Add(angle);
                    //足过度外翻 - 左    左侧外翻为+，内翻-， 右侧内翻为+，外翻-
                    angle = HermesCalculator.reqZuNeifanWaifanAngle3(float_array, 3, 5);
                    processAngleListList[m_currentState + 1, 2].Add(angle);
                    //足过度外翻 - 右   右侧内翻为+，外翻-
                    angle = HermesCalculator.reqZuNeifanWaifanAngle3(float_array, 4, 6);
                    processAngleListList[m_currentState + 1, 3].Add(angle);
                    //下蹲采取膝模式-
                    //骨盆前倾角度
                    angle = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 0, 0);
                    //膝盖屈角度-左
                    float angle2 = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                    //膝盖屈角度-右
                    float angle3 = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                    processAngleListList[m_currentState + 1, 4].Add(angle);
                    processAngleListList[m_currentState + 1, 5].Add(angle2);
                    processAngleListList[m_currentState + 1, 6].Add(angle3);
                }

                if(m_hermesStateStablization_List[m_currentState + 1].stablizedVariable[0] > -50 ||
                         m_hermesStateStablization_List[m_currentState + 1].stablizedVariable[1] > -50)
                {
                    if(processAngleListList[m_currentState + 1, 0].Count > 0)
                    {
                        processAngleListList[m_currentState + 1, 0].Clear();
                        processAngleListList[m_currentState + 1, 1].Clear();
                        processAngleListList[m_currentState + 1, 2].Clear();
                        processAngleListList[m_currentState + 1, 3].Clear();
                        processAngleListList[m_currentState + 1, 4].Clear();
                        processAngleListList[m_currentState + 1, 5].Clear();
                        processAngleListList[m_currentState + 1, 6].Clear();
                    }
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 150);                                                                                     //需要改-
            }
            else if (m_currentState == 1)                                                                                //需要改-
            {
                
            }

            if (m_successFlag == 1 && lineIndex % 100 == 0)
            {
                Console.WriteLine("测试时间结束！");                                                                                     //需要改
                m_tipFlag = 1;                                                                                     //需要改
                m_tipContent = "数据采集成功！\n请点击下一个动作\n继续";
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                if(m_successFlag != 1)
                {
                    Console.WriteLine("动作超时！");
                    m_successFlag = -1;
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "数据采集失败，\n请点击重做动作\n重做测试";
                }
                
                //if (lineIndex % 500 == 0)
                //{
                //    reset();
                //}
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();

            if (m_successFlag != 1)
            {
                m_successFlag = -1;
                Console.WriteLine("采集失败！");
                return ret;
            }

            //左侧膝内扣  //左腿内扣为+，外扣为-，右腿外扣为+，内扣为-
            double[] list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 0], 0, processAngleListList[0 + 1, 0].Count() - 1);
            ret.Add("3001", Math.Max((float)list[0], HermesCalculator.reqNeifanWaifanAngle4(stageEndStateList[1], 5, 3)  )  );
            Console.WriteLine("左侧膝内扣 " + Math.Max((float)list[0], HermesCalculator.reqNeifanWaifanAngle4(stageEndStateList[1], 5, 3)));
            //右侧膝内扣  //左腿内扣为+，外扣为-，右腿外扣为+，内扣为-
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 1], 0, processAngleListList[0 + 1, 1].Count() - 1);
            ret.Add("3002", Math.Max((float)-list[1], -HermesCalculator.reqNeifanWaifanAngle4(stageEndStateList[1], 6, 4)  )   );
            Console.WriteLine("右侧膝内扣 " + Math.Max(-(float)list[1], -HermesCalculator.reqNeifanWaifanAngle4(stageEndStateList[1], 6, 4)) + " " + (float)-list[1]);
            //左侧足过度外翻   //左侧外翻为+，内翻-， 右侧内翻为+，外翻-
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 2], 0, processAngleListList[0 + 1, 2].Count() - 1);   //方向正负？
            ret.Add("4001", (float)list[0]);
            Console.WriteLine("左侧足过度外翻 " + (float)list[0]);
            //右侧足过度外翻   //左侧外翻为+，内翻-， 右侧内翻为+，外翻-
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 3], 0, processAngleListList[0 + 1, 3].Count() - 1);   //方向正负？
            ret.Add("4002", -(float)list[1]);
            Console.WriteLine("右侧足过度外翻 " + -(float)list[1]);


            //骨盆前倾角度      
            float angle = HermesCalculator.reqYaobuQuShengAngleToGround(stageEndStateList[1], 0, 0) - HermesCalculator.reqYaobuQuShengAngleToGround(stageEndStateList[0], 0, 0);     //前倾为-，后倾为+
            //膝盖屈角度-左    
            float angle2 = HermesCalculator.reqYaobuQuShengAngleToGround(stageEndStateList[1], 0, 3) - HermesCalculator.reqYaobuQuShengAngleToGround(stageEndStateList[0], 0, 3);
            //膝盖屈角度-右    
            float angle3 = HermesCalculator.reqYaobuQuShengAngleToGround(stageEndStateList[1], 0, 4) - HermesCalculator.reqYaobuQuShengAngleToGround(stageEndStateList[0], 0, 4);

            //左侧膝模式, 越正越差
            ret.Add("3013", (float)angle - (float)(angle2) );
            Console.WriteLine("左侧膝模式 " + ((float)angle - (float)(angle2)) + " "+ ((float)angle) + " "+ ((float)angle2) + " ");
            //右侧膝模式, 越正越差
            ret.Add("3014", (float)angle - (float)(angle3) );
            Console.WriteLine("右侧膝模式 " + ((float)angle - (float)(angle3)) + " " + ((float)angle) + " " + ((float)angle3) + " ");

            //膝盖屈角度-左    
            float angle4 = HermesCalculator.reqQuShengAngle(stageEndStateList[1], 1, 3) - HermesCalculator.reqQuShengAngle(stageEndStateList[0], 1, 3);
            //膝盖屈角度-右    
            float angle5 = HermesCalculator.reqQuShengAngle(stageEndStateList[1], 2, 4) - HermesCalculator.reqQuShengAngle(stageEndStateList[0], 2, 4);
            //左侧下蹲角度
            ret.Add("30130", -(float)(angle4));
            //右侧下蹲角度
            ret.Add("30140", -(float)(angle5));

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ShenDun") == true)
            {
                HermesNewTest.m_tezhengDic_all["ShenDun"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ShenDun", ret);
            }

            return ret;
        }


    }     //状态检测器-深蹲

    public class HermesStateDetctorForZhengChangZou : HermesStateDetctor     //状态检测器-步态分析
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改--
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 25];                                 //需要改--
        int bodyTurnBackCount;
        int bodyTurnBackFlag;

        //初始化函数
        public HermesStateDetctorForZhengChangZou()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            bodyTurnBackCount = 0; 
            bodyTurnBackFlag = 0; 
            //准备阶段稳定器                                                                                     //需要改--
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedUp_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] expectedDown_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] stableUp_ = new float[] { 3, 3, 3, 3, 3, 3 };
            float[] stableDown_ = new float[] { 3, 3, 3, 3, 3, 3 };
            int numOfVariable_ = 6;                                                                           //需要改--
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改--
            preVariable_ = new float[] { 0 };
            expectedVariable_ = new float[] { 290};
            expectedUp_ = new float[] { 10};
            expectedDown_ = new float[] {0};
            stableUp_ = new float[] {0.1F};
            stableDown_ = new float[] {0.1F};
            numOfVariable_ = 1;                                                                             //需要改--
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 25; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改--
                float[] variable_ = new float[] { 0, 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1);
                variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 0, 2);
                variable_[2] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                variable_[3] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                variable_[4] = HermesCalculator.reqQuShengAngle(float_array, 3, 5);
                variable_[5] = HermesCalculator.reqQuShengAngle(float_array, 4, 6);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    if (lineIndex <= 0 || lineIndex >= 15 * 60 * 60 * 100)
                    {
                        Console.WriteLine("准备阶段采集失败！");                                                                                     //需要改---
                        m_tipFlag = 1;                                                                                     //需要改---
                        m_tipContent = "准备阶段采集失败！";                                                                                     //需要改---
                        m_prepFlag = -1;                                                                                     //需要改---
                        m_jindutiao = 0;                                                                                     //需要改---
                        return;
                    }

                    Console.WriteLine("准备阶段采集完成！");                                                                                     //需要改--
                    m_tipFlag = 1;                                                                                     //需要改--
                    m_tipContent = "准备阶段完成，请开始动作！";                                                                                     //需要改--
                    m_prepFlag = 1;                                                                                     //需要改--
                    m_jindutiao = 0;                                                                                     //需要改--
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改--
                float[] variable_ = new float[] { 0 };                                                                                     //需要改--
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1);    //需要改--
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改--
                    m_tipFlag = 0;                                                                                     //需要改--
                    m_tipContent = "动作采集完成，步态可以站起来了！";                                                                                     //需要改--
                    m_successFlag = 0;                                                                                      //需要改--
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime &&
                         m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 0 && bodyTurnBackCount <= 1)                        //需要改--
                {
                    //过程分析                                                                                                                      //需要改--
                    //任何时刻
                    //腰部前后倾
                    float yaobu_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 0].Add(yaobu_x);
                    //腰部旋转
                    float yaobu_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 2].Add(yaobu_z);
                    //左右摆动，向左-，向右+
                    float yaobu_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 1].Add(yaobu_y);

                    float angle = 0;
                    //髋关节屈伸左
                    angle = HermesCalculator.reqQuShengAngleToGround(float_array, 0, 1);
                    processAngleListList[m_currentState + 1, 3].Add(angle);
                    //髋关节屈伸右
                    angle = HermesCalculator.reqQuShengAngleToGround(float_array, 0, 2);
                    processAngleListList[m_currentState + 1, 4].Add(angle);
                    //髋关节外展左
                    angle = HermesCalculator.reqWaizhanNeishouAngleToBody(float_array, 0, 1);
                    processAngleListList[m_currentState + 1, 5].Add(angle);
                    //髋关节外展右
                    angle = HermesCalculator.reqWaizhanNeishouAngleToBody(float_array, 0, 2);
                    processAngleListList[m_currentState + 1, 6].Add(angle);

                    //膝关节屈伸左
                    angle = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                    processAngleListList[m_currentState + 1, 7].Add(angle);
                    //膝关节屈伸右
                    angle = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                    processAngleListList[m_currentState + 1, 8].Add(angle);
                    //膝关节内翻左
                    //angle = HermesCalculator.reqNeifanWaifanAngle4(float_array, 5, 3);
                    angle = HermesCalculator.reqButaineikouAngle(float_array, 1, 3);
                    processAngleListList[m_currentState + 1, 9].Add(angle);
                    //膝关节内翻右
                    //angle = HermesCalculator.reqNeifanWaifanAngle4(float_array, 6, 4);
                    angle = HermesCalculator.reqButaineikouAngle(float_array, 2, 4);
                    processAngleListList[m_currentState + 1, 10].Add(angle);
                    //小腿与地面夹角左
                    angle = HermesCalculator.reqXiaotuiToGroundAngle(float_array, 0, 3);
                    processAngleListList[m_currentState + 1, 11].Add(angle);
                    //小腿与地面夹角右
                    angle = HermesCalculator.reqXiaotuiToGroundAngle(float_array, 0, 4);
                    processAngleListList[m_currentState + 1, 12].Add(angle);

                    //脚面与地面的夹角左
                    angle = HermesCalculator.reqZuToGroundAngle(float_array, 3, 5);
                    processAngleListList[m_currentState + 1, 13].Add(angle);
                    //脚面与地面的夹角右
                    angle = HermesCalculator.reqZuToGroundAngle(float_array, 4, 6);
                    processAngleListList[m_currentState + 1, 14].Add(angle);
                    //足背屈-足趾屈左
                    angle = HermesCalculator.reqZuQuShengAngle(float_array, 3, 5);
                    processAngleListList[m_currentState + 1, 15].Add(angle);
                    //足背屈-足趾屈右
                    angle = HermesCalculator.reqZuQuShengAngle(float_array, 4, 6);
                    processAngleListList[m_currentState + 1, 16].Add(angle);
                    //足內翻，足外翻左
                    angle = HermesCalculator.reqZuNeifanWaifanAngle3(float_array, 3, 5);
                    processAngleListList[m_currentState + 1, 17].Add(angle);
                    //足內翻，足外翻右
                    angle = HermesCalculator.reqZuNeifanWaifanAngle3(float_array, 4, 6);
                    processAngleListList[m_currentState + 1, 18].Add(angle);
                    //足外旋，足内旋左
                    angle = HermesCalculator.reqZuNeixuanWaixuanAngle4(float_array, 3, 5);
                    processAngleListList[m_currentState + 1, 21].Add(angle);
                    //足外旋，足内旋右
                    angle = HermesCalculator.reqZuNeixuanWaixuanAngle4(float_array, 4, 6);
                    processAngleListList[m_currentState + 1, 22].Add(angle);

                    //时间
                    processAngleListList[m_currentState + 1, 19].Add(lineIndex);
                    //身体朝向
                    float[] yaobu = new float[3];
                    yaobu = HermesCalculator.reqMainAnglePosition(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 0);
                    angle = HermesCalculator.reqMainAngleLMNRelative(yaobu[0], yaobu[1], 0, 1, 0, 0);
                    processAngleListList[m_currentState + 1, 20].Add(angle);

                    if (angle > 80 || angle < -80){
                        if(bodyTurnBackFlag == 0)
                        {
                            bodyTurnBackFlag = 1;
                            bodyTurnBackCount++;
                        }
                        
                    }
                    else
                    {
                        if(bodyTurnBackFlag == 1)
                        {
                            bodyTurnBackFlag = 0;
                        }
                    }

                }
                else if (bodyTurnBackCount >= 2)
                {
                    m_currentState = 1;
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改--
                    m_tipFlag = 1;                                                                                     //需要改--
                    m_tipContent = "步态数据采集完成！";                                                                                     //需要改--
                    m_successFlag = 1;
                    return;
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改--
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 20000);                                                                                     //需要改--

                //更新进度条-在期望区间时

                m_jindutiao = (float)bodyTurnBackCount / 2.0F;
                if (m_jindutiao > 1)
                {
                    m_jindutiao = 1;
                }
                else if (m_jindutiao < 0)
                {
                    m_jindutiao = 0;
                }
            }
            else if (m_currentState == 1)                                                                                //需要改--
            {
                //需要改-
                m_jindutiao = (float)bodyTurnBackCount / 2.0F;
                if (m_jindutiao > 1)
                {
                    m_jindutiao = 1;
                }
                else if (m_jindutiao < 0)
                {
                    m_jindutiao = 0;
                }
            }

            if (m_successFlag == 1 && lineIndex % 100 == 0)
            {
                Console.WriteLine("测试时间结束！");                                                                                     //需要改
                m_tipFlag = 1;                                                                                     //需要改
                m_tipContent = "数据采集成功！\n请点击下一个动作\n继续";
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");                                                                             //需要改-
                if(m_successFlag != 1)
                {
                    m_successFlag = -1;
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "数据采集失败，\n请点击重做动作\n重做测试";
                }
                //if (lineIndex % 500 == 0)
                //{
                //    reset();
                //}
                //Console.WriteLine("动作采集完成！");                                                                                     //需要改--
                //m_tipFlag = 1;                                                                                     //需要改--
                //m_tipContent = "动作采集完成，请点击下一步！";                                                                                     //需要改--
                //m_successFlag = 1;                                                                                      //需要改--
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改-
        {
            Console.WriteLine("开始步态分析！ ");
            Dictionary<string, float> ret = new Dictionary<string, float>();


            
            //求地面与脚面的夹角最小值-左
            List<double> dimianjiajiao_left_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 13, 10);
            List<int> dimianjiajiao_min_left = HermesCalculator.huaxianValueDown(dimianjiajiao_left_pinhua, -15, 10);

            //求地面与脚面的夹角最大值-左
            List<int> dimianjiajiao_max_left = HermesCalculator.huaxianValueUp(dimianjiajiao_left_pinhua, 10, 10);

            if(dimianjiajiao_max_left.Count <= 3)
            {
                Console.Write("步态数据有误！");
                return ret;
            }

            //求地面与脚面的夹角最小值-右
            List<double> dimianjiajiao_right_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 14, 10);
            List<int> dimianjiajiao_min_right = HermesCalculator.huaxianValueDown(dimianjiajiao_right_pinhua, -15, 10);
            HermesCalculator.printList(dimianjiajiao_min_right, "地面与脚面的夹角最小值");

            //求地面与脚面的夹角最大值-右
            List<int> dimianjiajiao_max_right = HermesCalculator.huaxianValueUp(dimianjiajiao_right_pinhua, 10, 10);
            HermesCalculator.printList(dimianjiajiao_max_right, "地面与脚面的夹角最大值");

            if (dimianjiajiao_max_right.Count <= 3)
            {
                Console.Write("步态数据有误！");
                return ret;
            }

            //----------------------------------------------------------------------------------------------------------------

            //左
            //求脚接触地面时刻-左
            List<int> jiaojiechudimian_left = new List<int>();
            for (int i = 0; i < dimianjiajiao_max_left.Count(); i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    if (dimianjiajiao_max_left[i] + j < processAngleListList[0 + 1, 13].Count())
                    {
                        if (processAngleListList[0 + 1, 13][dimianjiajiao_max_left[i] + j] < 2.0)
                        {
                            jiaojiechudimian_left.Add(dimianjiajiao_max_left[i] + j);
                            break;
                        }
                    }
                }
            }

            //求脚离开地面时刻-左,在脚与地面夹角最高峰之间, 膝盖屈伸的第二个最高峰
            //膝盖伸平滑-左
            List<double> xigaiaiqushen_left_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 7, 10);
            //膝盖伸的最大值-左
            List<int> xigaiqushen_max_left = HermesCalculator.huaxianValueUp(xigaiaiqushen_left_pinhua, -50, 10);
            //脚离开地面时刻-左
            List<int> jiaolikaidimian_left = new List<int>();
            for (int i = 0; i < dimianjiajiao_max_left.Count() - 1; i++)
            {
                for (int j = 0; j < xigaiqushen_max_left.Count(); j++)
                {
                    if (xigaiqushen_max_left[j] > dimianjiajiao_max_left[i] + 30 && xigaiqushen_max_left[j] < dimianjiajiao_max_left[i + 1])
                    {
                        jiaolikaidimian_left.Add(xigaiqushen_max_left[j]);
                        break;
                    }
                }
            }

            //求膝盖屈伸最小值-左
            List<int> xigaiqushen_min_left = HermesCalculator.huaxianValueDown(xigaiaiqushen_left_pinhua, 10, 10);
            //左膝向前竖直时刻
            List<int> xigaishuzhi_left = new List<int>();
            for (int i = 0; i < xigaiqushen_min_left.Count(); i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    if (xigaiqushen_min_left[i] + j < processAngleListList[1, 11].Count())
                    {
                        if (processAngleListList[1, 11][xigaiqushen_min_left[i] + j] > -1 &&
                            processAngleListList[1, 11][xigaiqushen_min_left[i] + j] > processAngleListList[1, 11][xigaiqushen_min_left[i] + j - 1])
                        {
                            xigaishuzhi_left.Add(xigaiqushen_min_left[i] + j);
                            break;
                        }
                    }
                }
            }
            //去重
            xigaishuzhi_left = HermesCalculator.quchong(xigaishuzhi_left);

            //髋关节屈伸最小值-左
            List<double> datuiqushen_left_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 3, 10);
            List<int> datuiqushen_min_left = HermesCalculator.huaxianValueDown(datuiqushen_left_pinhua, 15, 10);
            HermesCalculator.printList(datuiqushen_min_left, "髋关节屈伸最小值-右");
            //髋关节屈伸最大值-左
            List<int> datuiqushen_max_left = HermesCalculator.huaxianValueUp(datuiqushen_left_pinhua, 10, 10);
            HermesCalculator.printList(datuiqushen_max_left, "髋关节屈伸最大值-右");
            //--------------------------------------------------------------------------------------------------------------
            //--------------------------------------------------------------------------------------------------------------
            //获得有效的一段-左侧
            //条件满足Flag
            int bodyTurn_left = -1;
            int bodyTurn_left_count = 0;
            int[] flagList = new int[30];
            List<int> startList_left = new List<int>();
            List<int> endList_left = new List<int>();
            for (int i = 0; i < dimianjiajiao_max_left.Count() - 1; i++)
            {
                int timeStart = dimianjiajiao_max_left[i];
                int timeStop = dimianjiajiao_max_left[i + 1];
                //身体朝向
                double bodyDirection = processAngleListList[0 + 1, 20][(int)((timeStart + timeStop) / 2)];
                //条件0, 地面与脚面的夹角最小值-左,有且只有一个
                flagList[0] = HermesCalculator.countInRange(dimianjiajiao_min_left, timeStart, timeStop, 6, 6);
                //条件1, 脚接触地面时刻-左,有且只有一个
                flagList[1] = HermesCalculator.countInRange(jiaojiechudimian_left, timeStart, timeStop, 6, 6);
                //条件2, 脚离开地面时刻-左,有且只有一个
                flagList[2] = HermesCalculator.countInRange(jiaolikaidimian_left, timeStart, timeStop, 6, 6);
                //条件3, 膝盖伸的最大值-左,有且只有二个
                flagList[3] = HermesCalculator.countInRange(xigaiqushen_max_left, timeStart, timeStop, 6, 6);
                //条件4, 膝盖屈伸最小值-左,有且只有二个
                flagList[4] = HermesCalculator.countInRange(xigaiqushen_min_left, timeStart, timeStop, 6, 6);
                //条件5, 左膝向前竖直时刻,有且只有一个
                flagList[5] = HermesCalculator.countInRange(xigaishuzhi_left, timeStart, timeStop, 6, 6);
                //条件6, 髋关节屈伸最小值 - 左,有且只有一个
                flagList[6] = HermesCalculator.countInRange(datuiqushen_min_left, timeStart, timeStop, 6, 6);
                //条件7, 髋关节屈伸最大值-左,有且只有二个
                flagList[7] = HermesCalculator.countInRange(datuiqushen_max_left, timeStart, timeStop, 6, 6);

                if (flagList[0] == 1 && flagList[1] == 1 && flagList[2] == 1 && flagList[3] == 3 &&
                   flagList[4] == 2 && flagList[5] == 1 && (flagList[6] == 2 || flagList[6] == 3 || flagList[6] == 1) && (flagList[7] == 2 || flagList[7] == 3 || flagList[7] == 1))
                {
                    if (bodyDirection < 80 && bodyDirection > -80)
                    {
                        if(bodyTurn_left == -1)
                        {
                            bodyTurn_left = 1;
                            bodyTurn_left_count++;
                        }
                        else if(bodyTurn_left == 1 && bodyTurn_left_count <= 2)
                        {
                            startList_left.Add(timeStart);
                            endList_left.Add(timeStop);
                        }
                    }
                    else
                    {
                        bodyTurn_left = -1;
                    }
                }
            }
            HermesCalculator.printList(startList_left, "开始");
            HermesCalculator.printList(endList_left, "结束");

            if (startList_left.Count <= 0)
            {
                Console.Write("步态数据有误！");
                return ret;
            }

            //获得特征

            List<double>[,] valueResultList_left = new List<double>[15, 4];
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    valueResultList_left[i, j] = new List<double>();
                }
            }
            for (int i = 0; i < startList_left.Count(); i++)
            {
                int timeStart = startList_left[i];
                int timeStop = endList_left[i];
                //足过度外翻-左
                int time1 = 0;
                for (int j = 0; j < jiaojiechudimian_left.Count(); j++)
                {
                    if (jiaojiechudimian_left[j] < timeStop && jiaojiechudimian_left[j] > timeStart)
                    {
                        time1 = jiaojiechudimian_left[j];
                    }
                }
                int time2 = 0;
                for (int j = 0; j < jiaolikaidimian_left.Count(); j++)
                {
                    if (jiaolikaidimian_left[j] < timeStop && jiaolikaidimian_left[j] > timeStart)
                    {
                        time2 = jiaolikaidimian_left[j];
                    }
                }
                double[] list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 17], time1, time2);
                for (int j = 0; j < 4; j++) valueResultList_left[0, j].Add(list[j]);

                //膝关节过伸-左
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 7], timeStart - 10, timeStart + 10);
                for (int j = 0; j < 4; j++) valueResultList_left[1, j].Add(list[j]);

                //后伸期大腿伸髋不足-后伸期 - 左
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 3], timeStart, timeStop);
                for (int j = 0; j < 4; j++) valueResultList_left[2, j].Add(list[j]);

                //摆动期过度髋外展 - 左
                int time = 0;
                for (int j = 0; j < xigaishuzhi_left.Count; j++)
                {
                    if (xigaishuzhi_left[j] < timeStop && xigaishuzhi_left[j] > timeStart)
                    {
                        time = xigaishuzhi_left[j];
                    }
                }
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 21], time, timeStop);
                for (int j = 0; j < 4; j++) valueResultList_left[3, j].Add(list[j]);

                //支撑期膝内扣 - 左
                time1 = 0;
                for (int j = 0; j < jiaojiechudimian_left.Count; j++)
                {
                    if (jiaojiechudimian_left[j] < timeStop && jiaojiechudimian_left[j] > timeStart)
                    {
                        time1 = jiaojiechudimian_left[j];
                    }
                }
                time2 = 0;
                for (int j = 0; j < jiaolikaidimian_left.Count; j++)
                {
                    if (jiaolikaidimian_left[j] < timeStop && jiaolikaidimian_left[j] > timeStart)
                    {
                        time2 = jiaolikaidimian_left[j];
                    }
                }
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 9], time1, time2);
                for (int j = 0; j < 4; j++) valueResultList_left[4, j].Add(list[j]);

                //后伸期背屈不足 - 左
                time = 0;
                for (int j = 0; j < datuiqushen_min_left.Count; j++)
                {
                    if (datuiqushen_min_left[j] < timeStop && datuiqushen_min_left[j] > timeStart)
                    {
                        time = datuiqushen_min_left[j];
                    }
                }
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 15], time - 10, time + 10);
                for (int j = 0; j < 4; j++) valueResultList_left[5, j].Add(list[j]);

                //两侧支撑期时间 - 左
                time1 = 0;
                for (int j = 0; j < jiaojiechudimian_left.Count; j++)
                {
                    if (jiaojiechudimian_left[j] < timeStop && jiaojiechudimian_left[j] > timeStart)
                    {
                        time1 = jiaojiechudimian_left[j];
                    }
                }
                time2 = 0;
                for (int j = 0; j < jiaolikaidimian_left.Count; j++)
                {
                    if (jiaolikaidimian_left[j] < timeStop && jiaolikaidimian_left[j] > timeStart)
                    {
                        time2 = jiaolikaidimian_left[j];
                    }
                }
                for (int j = 0; j < 4; j++) valueResultList_left[6, j].Add(time2 - time1);

                //支撑期内收过多 - 左
                time1 = 0;
                for (int j = 0; j < jiaojiechudimian_left.Count; j++)
                {
                    if (jiaojiechudimian_left[j] < timeStop && jiaojiechudimian_left[j] > timeStart)
                    {
                        time1 = jiaojiechudimian_left[j];
                    }
                }
                time2 = 0;
                for (int j = 0; j < jiaolikaidimian_left.Count; j++)
                {
                    if (jiaolikaidimian_left[j] < timeStop && jiaolikaidimian_left[j] > timeStart)
                    {
                        time2 = jiaolikaidimian_left[j];
                    }
                }
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 5], time1, time2);
                for (int j = 0; j < 4; j++) valueResultList_left[7, j].Add(list[j]);
            }

            HermesCalculator.printListDouble(valueResultList_left[0, 0], "足过度外翻-左 最大值");
            HermesCalculator.printListDouble(valueResultList_left[0, 1], "足过度外翻-左 最小值");

            HermesCalculator.printListDouble(valueResultList_left[1, 0], "膝关节过伸-左 最大值");

            HermesCalculator.printListDouble(valueResultList_left[2, 1], "腿伸髋不足-后伸期 - 左 最小值");

            HermesCalculator.printListDouble(valueResultList_left[3, 1], "摆动期过度髋外展 - 左 最大值");

            HermesCalculator.printListDouble(valueResultList_left[4, 0], "支撑期膝内扣 - 左 最大值");
            HermesCalculator.printListDouble(valueResultList_left[4, 1], "支撑期膝内扣 - 左 最小值");

            HermesCalculator.printListDouble(valueResultList_left[5, 0], "后伸期背屈不足 - 左 最大值");

            HermesCalculator.printListDouble(valueResultList_left[6, 0], "两侧支撑期时间 - 左 最大值");

            HermesCalculator.printListDouble(valueResultList_left[7, 0], "支撑期内收过多 - 左 最大值");


            Console.WriteLine("");
            Console.WriteLine("");

            //右
            //求脚接触地面时刻-右
            List<int> jiaojiechudimian_right = new List<int>();
            for (int i = 0; i < dimianjiajiao_max_right.Count(); i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    if(dimianjiajiao_max_right[i] + j < processAngleListList[0 + 1, 14].Count())
                    {
                        if (processAngleListList[0 + 1, 14][dimianjiajiao_max_right[i] + j] < 2.0)
                        {
                            jiaojiechudimian_right.Add(dimianjiajiao_max_right[i] + j);
                            break;
                        }
                    }
                }
            }
            HermesCalculator.printList(jiaojiechudimian_right, "求脚接触地面时刻-右");

            //求脚离开地面时刻-右,在脚与地面夹角最高峰之间, 膝盖屈伸的第二个最高峰
            //膝盖伸-右
            List<double> xigaiaiqushen_right_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 8, 10);
            //膝盖伸的最大值-右
            List<int> xigaiqushen_max_right = HermesCalculator.huaxianValueUp(xigaiaiqushen_right_pinhua, -50, 10);
            HermesCalculator.printList(xigaiqushen_max_right, "膝盖伸的最大值-右");
            //脚离开地面时刻-右
            List<int> jiaolikaidimian_right = new List<int>();
            for (int i = 0; i < dimianjiajiao_max_right.Count() - 1; i++)
            {
                for (int j = 0; j < xigaiqushen_max_right.Count(); j++)
                {
                    if (xigaiqushen_max_right[j] > dimianjiajiao_max_right[i] + 30 && xigaiqushen_max_right[j] < dimianjiajiao_max_right[i + 1])
                    {
                        jiaolikaidimian_right.Add(xigaiqushen_max_right[j]);
                        break;
                    }
                }
            }
            HermesCalculator.printList(jiaolikaidimian_right, "脚离开地面时刻-右");

            //求膝盖屈伸最小值-右
            List<int> xigaiqushen_min_right = HermesCalculator.huaxianValueDown(xigaiaiqushen_right_pinhua, 10, 10);
            HermesCalculator.printList(xigaiqushen_min_right, "求膝盖屈伸最小值-右");
            //右膝向前竖直时刻
            List<int> xigaishuzhi_right = new List<int>();
            for (int i = 0; i < xigaiqushen_min_right.Count(); i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    if (xigaiqushen_min_right[i] + j < processAngleListList[1, 12].Count())
                    {
                        if (processAngleListList[1, 12][xigaiqushen_min_right[i] + j] > -1 &&
                            processAngleListList[1, 12][xigaiqushen_min_right[i] + j] > processAngleListList[1, 12][xigaiqushen_min_right[i] + j - 1])
                        {
                            xigaishuzhi_right.Add(xigaiqushen_min_right[i] + j);
                            break;
                        }
                    }
                }
            }
            //去重
            xigaishuzhi_right = HermesCalculator.quchong(xigaishuzhi_right);
            HermesCalculator.printList(xigaishuzhi_right, "右膝向前竖直时刻");

            //髋关节屈伸最小值-右
            List<double> datuiqushen_right_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 4, 10);
            List<int> datuiqushen_min_right = HermesCalculator.huaxianValueDown(datuiqushen_right_pinhua, 15, 10);
            HermesCalculator.printList(datuiqushen_min_right, "髋关节屈伸最小值-右");
            //髋关节屈伸最大值-右
            List<int> datuiqushen_max_right = HermesCalculator.huaxianValueUp(datuiqushen_right_pinhua, 10, 10);
            HermesCalculator.printList(datuiqushen_max_right, "髋关节屈伸最大值-右");
            //--------------------------------------------------------------------------------------------------------------
            //--------------------------------------------------------------------------------------------------------------
            //获得有效的一段-右侧
            //条件满足Flag
            int bodyTurn_right = -1;
            int bodyTurn_right_count = 0;
            flagList = new int[30];
            List<int> startList_right = new List<int>();
            List<int> endList_right = new List<int>();
            for (int i = 0; i < dimianjiajiao_max_right.Count()-1; i++)
            {
                int timeStart = dimianjiajiao_max_right[i];
                int timeStop = dimianjiajiao_max_right[i+1];
                //身体朝向
                double bodyDirection = processAngleListList[0 + 1, 20][(int)((timeStart + timeStop)/2)];
                //条件0, 地面与脚面的夹角最小值-右,有且只有一个
                flagList[0] = HermesCalculator.countInRange(dimianjiajiao_min_right, timeStart, timeStop, 6, 6);
                //条件1, 脚接触地面时刻-右,有且只有一个
                flagList[1] = HermesCalculator.countInRange(jiaojiechudimian_right, timeStart, timeStop, 6, 6);
                //条件2, 脚离开地面时刻-右,有且只有一个
                flagList[2] = HermesCalculator.countInRange(jiaolikaidimian_right, timeStart, timeStop, 6, 6);
                //条件3, 膝盖伸的最大值-右,有且只有二个
                flagList[3] = HermesCalculator.countInRange(xigaiqushen_max_right, timeStart, timeStop, 6, 6);
                //条件4, 膝盖屈伸最小值-右,有且只有二个
                flagList[4] = HermesCalculator.countInRange(xigaiqushen_min_right, timeStart, timeStop, 6, 6);
                //条件5, 右膝向前竖直时刻,有且只有一个
                flagList[5] = HermesCalculator.countInRange(xigaishuzhi_right, timeStart, timeStop, 6, 6);
                //条件6, 髋关节屈伸最小值 - 右,有且只有二个或者一个或者三个
                flagList[6] = HermesCalculator.countInRange(datuiqushen_min_right, timeStart, timeStop, 6, 6);
                //条件7, 髋关节屈伸最大值-右,有且只有二个或者一个或者三个
                flagList[7] = HermesCalculator.countInRange(datuiqushen_max_right, timeStart, timeStop, 6, 6);

                if(flagList[0] == 1 && flagList[1] == 1 && flagList[2] == 1 && flagList[3] == 3 && 
                   flagList[4] == 2 && flagList[5] == 1 && (flagList[6] == 2 || flagList[6] == 3 || flagList[6] == 1) && (flagList[7] == 2 || flagList[7] == 3 || flagList[7] == 1))
                {
                    if(bodyDirection < 80 && bodyDirection > -80)
                    {

                        if(bodyTurn_right == -1)
                        {
                            bodyTurn_right = 1;
                            bodyTurn_right_count++;
                        }
                        else if(bodyTurn_right == 1 && bodyTurn_right_count <= 2)
                        {
                            startList_right.Add(timeStart);
                            endList_right.Add(timeStop);
                        }
                    }
                    else
                    {
                        bodyTurn_right = -1;
                    }
                }
            }
            HermesCalculator.printList(startList_right, "开始");
            HermesCalculator.printList(endList_right, "结束");

            if (startList_right.Count <= 0)
            {
                Console.Write("步态数据有误！");
                return ret;
            }

            //获得特征
            //Dictionary<string, float> ret = new Dictionary<string, float>();
            List<double>[,] valueResultList_right = new List<double>[15,4];
            for (int i = 0; i < 15; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    valueResultList_right[i, j] = new List<double>();
                }
            }
            for (int i = 0; i < startList_right.Count(); i++)
            {
                int timeStart = startList_right[i];
                int timeStop = endList_right[i];
                //足过度外翻-右
                int time1 = 0;
                for (int j = 0; j < jiaojiechudimian_right.Count; j++)
                {
                    if (jiaojiechudimian_right[j] < timeStop && jiaojiechudimian_right[j] > timeStart)
                    {
                        time1 = jiaojiechudimian_right[j];
                    }
                }
                int time2 = 0;
                for (int j = 0; j < jiaolikaidimian_right.Count; j++)
                {
                    if (jiaolikaidimian_right[j] < timeStop && jiaolikaidimian_right[j] > timeStart)
                    {
                        time2 = jiaolikaidimian_right[j];
                    }
                }
                double[] list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 18], time1, time2);
                for (int j = 0; j < 4; j++) valueResultList_right[0, j].Add(list[j]);

                //膝关节过伸-右
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 8], timeStart-10, timeStart+10);
                for (int j = 0; j < 4; j++) valueResultList_right[1, j].Add(list[j]);

                //后伸期大腿伸髋不足-后伸期 - 右
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 4], timeStart, timeStop);
                for (int j = 0; j < 4; j++) valueResultList_right[2, j].Add(list[j]);

                //摆动期过度髋外展 - 右
                int time = 0;
                for (int j = 0; j < xigaishuzhi_right.Count; j++)
                {
                    if(xigaishuzhi_right[j] < timeStop && xigaishuzhi_right[j] > timeStart)
                    {
                        time = xigaishuzhi_right[j];
                    }
                }
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 22], time, timeStop);
                for (int j = 0; j < 4; j++) valueResultList_right[3, j].Add(list[j]);

                //支撑期膝内扣 - 右
                time1 = 0;
                for (int j = 0; j < jiaojiechudimian_right.Count; j++)
                {
                    if (jiaojiechudimian_right[j] < timeStop && jiaojiechudimian_right[j] > timeStart)
                    {
                        time1 = jiaojiechudimian_right[j];
                    }
                }
                time2 = 0;
                for (int j = 0; j < jiaolikaidimian_right.Count; j++)
                {
                    if (jiaolikaidimian_right[j] < timeStop && jiaolikaidimian_right[j] > timeStart)
                    {
                        time2 = jiaolikaidimian_right[j];
                    }
                }
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 10], time1, time2);
                for (int j = 0; j < 4; j++) valueResultList_right[4, j].Add(list[j]);

                //后伸期背屈不足 - 右
                time = 0;
                for (int j = 0; j < datuiqushen_min_right.Count; j++)
                {
                    if (datuiqushen_min_right[j] < timeStop && datuiqushen_min_right[j] > timeStart)
                    {
                        time = datuiqushen_min_right[j];
                    }
                }
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 16], time-10, time + 10);
                for (int j = 0; j < 4; j++) valueResultList_right[5, j].Add(list[j]);

                //两侧支撑期时间 - 右
                time1 = 0;
                for (int j = 0; j < jiaojiechudimian_right.Count; j++)
                {
                    if (jiaojiechudimian_right[j] < timeStop && jiaojiechudimian_right[j] > timeStart)
                    {
                        time1 = jiaojiechudimian_right[j];
                    }
                }
                time2 = 0;
                for (int j = 0; j < jiaolikaidimian_right.Count; j++)
                {
                    if (jiaolikaidimian_right[j] < timeStop && jiaolikaidimian_right[j] > timeStart)
                    {
                        time2 = jiaolikaidimian_right[j];
                    }
                }
                for (int j = 0; j < 4; j++) valueResultList_right[6, j].Add(time2 - time1);

                //支撑期内收过多 - 右
                time1 = 0;
                for (int j = 0; j < jiaojiechudimian_right.Count; j++)
                {
                    if (jiaojiechudimian_right[j] < timeStop && jiaojiechudimian_right[j] > timeStart)
                    {
                        time1 = jiaojiechudimian_right[j];
                    }
                }
                time2 = 0;
                for (int j = 0; j < jiaolikaidimian_right.Count; j++)
                {
                    if (jiaolikaidimian_right[j] < timeStop && jiaolikaidimian_right[j] > timeStart)
                    {
                        time2 = jiaolikaidimian_right[j];
                    }
                }
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 6], time1, time2);
                for (int j = 0; j < 4; j++) valueResultList_right[7, j].Add(list[j]);

                //骨盆旋转
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 2], timeStart, timeStop);
                for (int j = 0; j < 4; j++) valueResultList_right[8, j].Add(list[j]);

                //骨盆左右倾
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 1], timeStart, timeStop);
                for (int j = 0; j < 4; j++) valueResultList_right[9, j].Add(list[j]);

                //骨盆前后倾
                list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 0], timeStart, timeStop);
                for (int j = 0; j < 4; j++) valueResultList_right[10, j].Add(list[j]);
            }
            HermesCalculator.printListDouble(valueResultList_right[0, 0], "足过度外翻-右 最大值");
            HermesCalculator.printListDouble(valueResultList_right[0, 1], "足过度外翻-右 最小值");

            HermesCalculator.printListDouble(valueResultList_right[1, 0], "膝关节过伸-右 最大值");

            HermesCalculator.printListDouble(valueResultList_right[2, 1], "腿伸髋不足-后伸期 - 右 最小值");

            HermesCalculator.printListDouble(valueResultList_right[3, 0], "摆动期过度髋外展 - 右 最大值");

            HermesCalculator.printListDouble(valueResultList_right[4, 0], "支撑期膝内扣 - 右 最大值");
            HermesCalculator.printListDouble(valueResultList_right[4, 1], "支撑期膝内扣 - 右 最小值");

            HermesCalculator.printListDouble(valueResultList_right[5, 0], "后伸期背屈不足 - 右 最大值");

            HermesCalculator.printListDouble(valueResultList_right[6, 0], "两侧支撑期时间 - 右 最大值");

            HermesCalculator.printListDouble(valueResultList_right[7, 0], "支撑期内收过多 - 右 最大值");

            HermesCalculator.printListDouble(valueResultList_right[8, 0], "骨盆旋转 最大值");
            HermesCalculator.printListDouble(valueResultList_right[8, 1], "骨盆旋转 最小值");
            HermesCalculator.printListDouble(valueResultList_right[8, 2], "骨盆旋转 平均值");
            HermesCalculator.printListDouble(valueResultList_right[8, 3], "骨盆旋转 方差值");

            HermesCalculator.printListDouble(valueResultList_right[9, 0], "骨盆左右倾 最大值");
            HermesCalculator.printListDouble(valueResultList_right[9, 1], "骨盆左右倾 最小值");
            HermesCalculator.printListDouble(valueResultList_right[9, 2], "骨盆左右倾 平均值");
            HermesCalculator.printListDouble(valueResultList_right[9, 3], "骨盆左右倾 方差值");

            HermesCalculator.printListDouble(valueResultList_right[10, 0], "骨盆前后倾 最大值");
            HermesCalculator.printListDouble(valueResultList_right[10, 1], "骨盆前后倾 最小值");
            HermesCalculator.printListDouble(valueResultList_right[10, 2], "骨盆前后倾 平均值");
            HermesCalculator.printListDouble(valueResultList_right[10, 3], "骨盆前后倾 方差值");

            Console.WriteLine("");
            Console.WriteLine("");

            //左侧足外翻过度  //左侧外翻为+，内翻-， 右侧内翻为+，外翻-
            ret.Add("4001", (float)HermesCalculator.Ave(valueResultList_left[0, 0].ToArray()));
            Console.WriteLine("左侧足外翻过度: " + (float)HermesCalculator.Ave(valueResultList_left[0, 0].ToArray()));
            //左侧膝关节过伸
            ret.Add("3011", (float)HermesCalculator.Ave(valueResultList_left[1, 0].ToArray()) - HermesCalculator.reqQuShengAngle(stageEndStateList[0], 1, 3)  );
            Console.WriteLine("左侧膝关节过伸: " + ((float)HermesCalculator.Ave(valueResultList_left[1, 0].ToArray()) - HermesCalculator.reqQuShengAngle(stageEndStateList[0], 1, 3))  );
            //左侧腿伸髋不足-后伸期
            ret.Add("2003", -(float)HermesCalculator.Ave(valueResultList_left[2, 1].ToArray()));
            Console.WriteLine("左侧腿伸髋不足-后伸期: " + -(float)HermesCalculator.Ave(valueResultList_left[2, 1].ToArray()));
            //左侧摆动期过度髋外展   //左侧外旋为-，内旋+， 右侧内旋为-，外旋+
            ret.Add("2001", -(float)HermesCalculator.Ave(valueResultList_left[3, 1].ToArray()));
            Console.WriteLine("左侧摆动期过度髋外展: " + -(float)HermesCalculator.Ave(valueResultList_left[3, 1].ToArray()));
            //左侧支撑期膝内扣     //左腿内扣为+，外扣为-，右腿外扣为+，内扣为-
            ret.Add("3001", (float)HermesCalculator.Ave(valueResultList_left[4, 0].ToArray()));
            Console.WriteLine("左侧支撑期膝内扣: " + (float)HermesCalculator.Ave(valueResultList_left[4, 0].ToArray()));
            //左侧后伸期背屈不足   //背屈为+，跖屈为-
            ret.Add("4007", (float)HermesCalculator.Ave(valueResultList_left[5, 0].ToArray()));
            Console.WriteLine("左侧后伸期背屈不足: " + (float)HermesCalculator.Ave(valueResultList_left[5, 0].ToArray()));
            //左侧支撑期内收过多   //左腿外展+，内收-，右腿外展-，内收+
            ret.Add("2014", -(float)HermesCalculator.Ave(valueResultList_left[7, 1].ToArray()));
            Console.WriteLine("左侧支撑期内收过多: " + -(float)HermesCalculator.Ave(valueResultList_left[7, 1].ToArray()));

            //右侧足外翻过度   //左侧外翻为+，内翻-， 右侧内翻为+，外翻-
            ret.Add("4002", -(float)HermesCalculator.Ave(valueResultList_right[0, 1].ToArray()));
            Console.WriteLine("右侧足外翻过度: " + -(float)HermesCalculator.Ave(valueResultList_right[0, 1].ToArray()));
            //右侧膝关节过伸
            ret.Add("3012", (float)HermesCalculator.Ave(valueResultList_right[1, 0].ToArray()) - HermesCalculator.reqQuShengAngle(stageEndStateList[0], 2, 4)  );
            Console.WriteLine("右侧膝关节过伸: " + ((float)HermesCalculator.Ave(valueResultList_right[1, 0].ToArray()) - HermesCalculator.reqQuShengAngle(stageEndStateList[0], 2, 4))  );
            //右侧腿伸髋不足-后伸期
            ret.Add("2004", -(float)HermesCalculator.Ave(valueResultList_right[2, 1].ToArray()));
            Console.WriteLine("右侧腿伸髋不足-后伸期: " + -(float)HermesCalculator.Ave(valueResultList_right[2, 1].ToArray()));
            //右侧摆动期过度髋外展   //左侧外旋为-，内旋+， 右侧内旋为-，外旋+
            ret.Add("2002", (float)HermesCalculator.Ave(valueResultList_right[3, 0].ToArray()));
            Console.WriteLine("右侧摆动期过度髋外展: " + (float)HermesCalculator.Ave(valueResultList_right[3, 0].ToArray()));
            //右侧支撑期膝内扣   //左腿内扣为+，外扣为-，右腿外扣为+，内扣为-
            ret.Add("3002", -(float)HermesCalculator.Ave(valueResultList_right[4, 1].ToArray()));
            Console.WriteLine("右侧支撑期膝内扣: " + -(float)HermesCalculator.Ave(valueResultList_right[4, 1].ToArray()));
            //右侧后伸期背屈不足    //背屈为+，跖屈为-
            ret.Add("4008", (float)HermesCalculator.Ave(valueResultList_right[5, 0].ToArray()));
            Console.WriteLine("右侧后伸期背屈不足: " + (float)HermesCalculator.Ave(valueResultList_right[5, 0].ToArray()));
            //右侧支撑期内收过多    //左腿外展+，内收-，右腿外展-，内收+
            ret.Add("2015", (float)HermesCalculator.Ave(valueResultList_right[7, 0].ToArray()));
            Console.WriteLine("右侧支撑期内收过多: " + (float)HermesCalculator.Ave(valueResultList_right[7, 0].ToArray()));
            //两侧支撑时间不同（左侧-右侧）
            ret.Add("5009", ((float)HermesCalculator.Ave(valueResultList_left[6, 0].ToArray())  -   (float)HermesCalculator.Ave(valueResultList_right[6, 0].ToArray()) ) * 10F- 0);
            Console.WriteLine("两侧支撑时间不同（左侧-右侧）: " + ((float)HermesCalculator.Ave(valueResultList_left[6, 0].ToArray()) - (float)HermesCalculator.Ave(valueResultList_right[6, 0].ToArray()) - 0) * 10F);
            //两侧支撑时间不同（右侧-左侧）
            ret.Add("5010", (float)HermesCalculator.Ave(valueResultList_right[6, 0].ToArray()) - (float)HermesCalculator.Ave(valueResultList_left[6, 0].ToArray()) * 10F - 0);
            Console.WriteLine("两侧支撑时间不同（右侧-左侧）: " + ((float)HermesCalculator.Ave(valueResultList_right[6, 0].ToArray()) - (float)HermesCalculator.Ave(valueResultList_left[6, 0].ToArray()) - 0) * 10F);

            //腰部前后倾
            float yaobu_y = HermesCalculator.reqYaobuQuShengAngleToGround(stageEndStateList[0], 0, 0) ;
            //腰部旋转
            float yaobu_z = HermesCalculator.reqNeixuanWaiXuanAngle3(stageEndStateList[0], 0, 0);
            //左右摆动，向左-，向右+
            float yaobu_x = HermesCalculator.reqWaizhanNeishouAngleToGround3(stageEndStateList[0], 0, 0);

            //骨盆左倾过度  //骨盆左右摆动，向左-，向右+
            ret.Add("1001", -(float)HermesCalculator.Ave(valueResultList_right[9, 1].ToArray()) + yaobu_x );
            Console.WriteLine("骨盆左倾过度: " + (-(float)HermesCalculator.Ave(valueResultList_right[9, 1].ToArray()) + yaobu_x) + ' ' + yaobu_x + ' ' + (float)HermesCalculator.Ave(valueResultList_right[9, 1].ToArray()));
            //骨盆右倾过度   //骨盆左右摆动，向左-，向右+
            ret.Add("1002", (float)HermesCalculator.Ave(valueResultList_right[9, 0].ToArray()) - yaobu_x );
            Console.WriteLine("骨盆右倾过度: " + ((float)HermesCalculator.Ave(valueResultList_right[9, 0].ToArray()) - yaobu_x) + ' ' + yaobu_x + ' ' + (float)HermesCalculator.Ave(valueResultList_right[9, 0].ToArray()));
            //骨盆顺时针旋转过度   腰部右旋顺时针+，左旋逆时针-
            ret.Add("1003", (float)HermesCalculator.Ave(valueResultList_right[8, 0].ToArray()) - yaobu_z );
            Console.WriteLine("骨盆顺时针旋转过度: " + ((float)HermesCalculator.Ave(valueResultList_right[8, 0].ToArray()) - yaobu_z) + ' ' + yaobu_z + ' ' + (float)HermesCalculator.Ave(valueResultList_right[8, 0].ToArray()));
            //骨盆逆时针旋转过度   腰部右旋顺时针+，左旋逆时针-
            ret.Add("1004", -(float)HermesCalculator.Ave(valueResultList_right[8, 1].ToArray()) + yaobu_z );
            Console.WriteLine("骨盆逆时针旋转过度: " + (-(float)HermesCalculator.Ave(valueResultList_right[8, 1].ToArray()) + yaobu_z) + ' ' + yaobu_z + ' ' + (float)HermesCalculator.Ave(valueResultList_right[8, 1].ToArray()));
            //骨盆前倾过度    //前倾-，后倾+
            ret.Add("1005", -(float)HermesCalculator.Ave(valueResultList_right[10, 1].ToArray()) + yaobu_y );
            Console.WriteLine("骨盆前倾过度: " + (-(float)HermesCalculator.Ave(valueResultList_right[10, 1].ToArray()) + yaobu_y) );
            //骨盆后倾过度   //前倾-，后倾+
            ret.Add("1006", (float)HermesCalculator.Ave(valueResultList_right[10, 0].ToArray()) - yaobu_y );
            Console.WriteLine("骨盆后倾过度: " + ((float)HermesCalculator.Ave(valueResultList_right[10, 0].ToArray()) - yaobu_y) );

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("DaBuZou") == true)
            {
                HermesNewTest.m_tezhengDic_all["DaBuZou"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("DaBuZou", ret);
            }

            return ret;
        }


    }     //状态检测器-步态分析

    public class HermesStateDetctorForZuoCeDanTuiDun : HermesStateDetctor     //状态检测器-单腿蹲-左
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改--
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];
        //下蹲最大值
        public double xiadunMin;
        //加速度计数器
        double accCount;
        //加速度积分变量存储器-左脚
        public float[] accIntegralArrayLeft = new float[3];
        //加速度积分变量存储器-右脚
        public float[] accIntegralArrayRight = new float[3];


        //初始化函数
        public HermesStateDetctorForZuoCeDanTuiDun()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            xiadunMin = 0;
            accCount = 0;
            accIntegralArrayLeft[0] = 0; accIntegralArrayLeft[1] = 0; accIntegralArrayLeft[2] = -1;
            accIntegralArrayRight[0] = 0; accIntegralArrayRight[1] = 0; accIntegralArrayRight[2] = -1;
            //准备阶段稳定器                                                                                     //需要改--
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedUp_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] expectedDown_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] stableUp_ = new float[] { 3, 3, 3, 3, 3, 3 };
            float[] stableDown_ = new float[] { 3, 3, 3, 3, 3, 3 };
            int numOfVariable_ = 6;
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改--
            preVariable_ = new float[] { 270 };
            expectedVariable_ = new float[] { 270 };
            expectedUp_ = new float[] { 15 };
            expectedDown_ = new float[] { 100 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改--
                float[] variable_ = new float[] { 0, 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1);
                variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 0, 2);
                variable_[2] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                variable_[3] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                variable_[4] = HermesCalculator.reqQuShengAngle(float_array, 3, 5);
                variable_[5] = HermesCalculator.reqQuShengAngle(float_array, 4, 6);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    if (lineIndex <= 0 || lineIndex >= 15 * 60 * 60 * 100)
                    {
                        Console.WriteLine("准备阶段采集失败！");                                                                                     //需要改---
                        m_tipFlag = 1;                                                                                     //需要改---
                        m_tipContent = "准备阶段采集失败！";                                                                                     //需要改---
                        m_prepFlag = -1;                                                                                     //需要改---
                        m_jindutiao = 0;                                                                                     //需要改---
                        return;
                    }

                    Console.WriteLine("准备阶段采集完成！");                                                                                     //需要改--
                    m_tipFlag = 1;                                                                                     //需要改--
                    m_tipContent = "准备阶段采集完成！";                                                                                     //需要改--
                    m_prepFlag = 1;                                                                                     //需要改--
                    m_jindutiao = 0;                                                                                     //需要改--
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0 };                                                                                     //需要改--
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);    //需要改--
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1 && xiadunMin < -40 && variable_[0] > -15)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改--
                    m_tipFlag = 1;                                                                                     //需要改--
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改--
                    m_successFlag = 1;                                                                                      //需要改--
                    m_jindutiao = 1;
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析                                                                                                                      //需要改--
                    //上升时刻
                    if (m_hermesStateStablization_List[m_currentState + 1].isDownStage[0] == 1 && variable_[0] <= xiadunMin && variable_[0] < -15)
                    {
                        if (variable_[0] < -50)
                        {
                            //膝内扣角度 - 左
                            float angle1 = HermesCalculator.reqNeifanWaifanAngle4(float_array, 5, 3);
                            processAngleListList[m_currentState + 1, 0].Add(angle1);

                            //下蹲晃动-左
                            angle1 = HermesCalculator.reqNeifanWaifanAngle4(float_array, 5, 3);
                            processAngleListList[m_currentState + 1, 4].Add(angle1);
                        }

                        //下蹲幅度 - 左
                        float angle = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                        processAngleListList[m_currentState + 1, 2].Add(angle);

                        //骨盆左右倾
                        angle = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 6].Add(angle);

                    }

                    //更新加速度积分
                    float[] distanceLeft = HermesCalculator.reqAccToDistance(float_array, 5, accIntegralArrayLeft[0], accIntegralArrayLeft[1], (int)accIntegralArrayLeft[2], lineIndex);
                    accIntegralArrayLeft[0] = distanceLeft[0];
                    accIntegralArrayLeft[1] = distanceLeft[1];
                    accIntegralArrayLeft[2] = distanceLeft[2];
                    float[] distanceRight = HermesCalculator.reqAccToDistance(float_array, 6, accIntegralArrayRight[0], accIntegralArrayRight[1], (int)accIntegralArrayRight[2], lineIndex);
                    accIntegralArrayRight[0] = distanceRight[0];
                    accIntegralArrayRight[1] = distanceRight[1];
                    accIntegralArrayRight[2] = distanceRight[2];

                    if (HermesCalculator.reqAccMaxTotal(float_array, 5) > 1.6)
                    {
                        accCount += HermesCalculator.reqAccMaxTotal(float_array, 5);
                    }
                    if (( (Math.Abs(accIntegralArrayLeft[0])  > Math.Abs(accIntegralArrayRight[0])) || accCount > 15) && xiadunMin < -60 )
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的左脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的左脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = 1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        accCount = 2000;
                        return;
                    }
                    if (( (Math.Abs(accIntegralArrayLeft[0]) > Math.Abs(accIntegralArrayRight[0])) || accCount > 3) && xiadunMin > -60 )
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的左脚移动了\n请注意是左脚支撑下蹲\n不是右脚\n动作采集失败\n请点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的左脚移动了\n请注意是左脚支撑下蹲\n不是右脚\n动作采集失败\n请点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = -1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        return;
                    }
                    if (HermesCalculator.reqAccMaxTotal(float_array, 6) > 3.0 && xiadunMin < -60)
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = 1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        accCount = 1000;
                        return;
                    }
                    if (HermesCalculator.reqAccMaxTotal(float_array, 6) > 3.0 && xiadunMin > -60)
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = 1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        accCount = 3000;
                        return;
                    }

                }

                if (xiadunMin > variable_[0])
                {
                    xiadunMin = variable_[0];
                }

                //更新进度条-在期望区间时
                m_jindutiao = (float)xiadunMin / (float)-100;
                if (m_jindutiao > 1)
                {
                    m_jindutiao = 1;
                }
                else if (m_jindutiao < 0)
                {
                    m_jindutiao = 0;
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改--
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 50);                                                                                     //需要改--
            }
            else if (m_currentState == 1)                                                                                //需要改--
            {

            }

            if (m_successFlag == 1 && lineIndex % 100 == 0 && accCount <= 100)
            {
                Console.WriteLine("数据采集成功！");                                                                                     //需要改
                m_tipFlag = 1;                                                                                     //需要改
                m_tipContent = "数据采集成功！\n请点击下一个动作\n继续";
            }
            else if (m_successFlag == 1 && lineIndex % 100 == 0 && accCount > 3 && accCount == 2000)
            {
                Console.WriteLine("系统检测到您的左脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                              //需要改--
                m_tipFlag = 1;                                                                                     //需要改--
                m_tipContent = "系统检测到您的左脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";
            }
            else if (m_successFlag == -1 && lineIndex % 100 == 0 && accCount > 3 && accCount < 500)
            {
                Console.WriteLine("系统检测到您的左脚移动了\n请注意是左脚支撑下蹲\n不是右脚\n动作采集失败\n请点击小程序上的重试按钮重做");                                                                                     //需要改
                m_tipFlag = 1;                                                                                     //需要改
                m_tipContent = "系统检测到您的左脚移动了\n请注意是左脚支撑下蹲\n不是右脚\n动作采集失败\n请点击小程序上的重试按钮重做";
            }
            else if (m_successFlag == 1 && lineIndex % 100 == 0 && accCount == 1000)
            {
                Console.WriteLine("系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                m_tipFlag = 1;                                                                                     //需要改--
                m_tipContent = "系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";
            }
            else if (m_successFlag == 1 && lineIndex % 100 == 0 && accCount == 3000)
            {
                Console.WriteLine("系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                m_tipFlag = 1;                                                                                     //需要改--
                m_tipContent = "系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "数据采集失败，\n请点击重做动作\n重做测试";
                }

            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();

            if (xiadunMin > -40)
            {
                //下蹲幅度 - 左
                ret.Add("30150", (float)-xiadunMin);
                return ret;
            }

            //左侧膝内扣  //左腿内扣为+，外扣为-，右腿外扣为+，内扣为-
            double[] list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 0], 0, processAngleListList[0 + 1, 0].Count() - 1);
            ret.Add("3001", (float)list[0]);
            Console.WriteLine("左侧膝内扣 " + (float)list[0]);

            //下蹲幅度 - 左    //-
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 2], 0, processAngleListList[0 + 1, 2].Count() - 1);
            ret.Add("30150", -(float)list[1]);
            Console.WriteLine("下蹲幅度 - 左 真" + ret["30150"]);

            if (accCount == 2000 || accCount == 1000 || accCount == 3000)
            {
                //下蹲幅度 - 左
                ret["30150"] = (float)40;
                //return ret;
                Console.WriteLine("下蹲幅度 - 左 假" + ret["30150"]);
            }


            if (HermesNewTest.m_tezhengDic_all.ContainsKey("YouCeDanTuiDun") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].ContainsKey("30160") == true)
                {
                    float zuoce = ret["30150"];
                    float youce = HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"]["30160"];
                    //两侧下蹲幅度不同（左侧-右侧）
                    ret.Add("3015", zuoce - youce);
                    if (HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].ContainsKey("3016") == true)
                    {
                        //两侧下蹲幅度不同（右侧 - 左侧）
                        HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"]["3016"] = youce - zuoce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].Add("3016", youce - zuoce);
                    }
                }
            }

            //下蹲晃动-左
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 4], 0, processAngleListList[0 + 1, 4].Count() - 1);
            ret.Add("50010", (float)list[0] - (float)list[1]);
            Console.WriteLine("下蹲晃动-左 " + ((float)list[0] - (float)list[1]) + " " + (float)list[0] + " " + (float)list[1]);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("YouCeDanTuiDun") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].ContainsKey("50020") == true)
                {
                    float zuoce = ret["50010"];
                    float youce = HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"]["50020"];
                    //两侧下蹲晃动不同（左侧-右侧）
                    ret.Add("5001", zuoce - youce);
                    if (HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].ContainsKey("5002") == true)
                    {
                        //两侧下蹲晃动不同（右侧 - 左侧）
                        HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"]["5002"] = youce - zuoce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].Add("5002", youce - zuoce);
                    }
                }
            }


            //骨盆左右倾  //骨盆左右摆动，向左-，向右+
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 6], 0, processAngleListList[0 + 1, 6].Count() - 1);
            //骨盆左倾角度
            ret.Add("1001", -(float)list[1]);
            Console.WriteLine("骨盆左倾角度 " + -(float)list[1]);
            //骨盆右倾角度
            ret.Add("1002", (float)list[0]);
            Console.WriteLine("骨盆右倾角度 " + (float)list[0]);


            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoCeDanTuiDun") == true)
            {
                HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ZuoCeDanTuiDun", ret);
            }

            return ret;
        }


    }     //状态检测器-单腿蹲-左-新版本,有加速度积分

    public class HermesStateDetctorForZuoCeDanTuiDunOld : HermesStateDetctor     //状态检测器-单腿蹲-左
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改--
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];
        //下蹲最大值
        double xiadunMin;
        //加速度计数器
        double accCount;

        //初始化函数
        public HermesStateDetctorForZuoCeDanTuiDunOld()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            xiadunMin = 0;
            accCount = 0;
            //准备阶段稳定器                                                                                     //需要改--
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedUp_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] expectedDown_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] stableUp_ = new float[] { 3, 3, 3, 3, 3, 3 };
            float[] stableDown_ = new float[] { 3, 3, 3, 3, 3, 3 };
            int numOfVariable_ = 6;
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改--
            preVariable_ = new float[] { 270 };
            expectedVariable_ = new float[] { 270 };
            expectedUp_ = new float[] { 15 };
            expectedDown_ = new float[] { 100};
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改--
                float[] variable_ = new float[] { 0, 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1);
                variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 0, 2);
                variable_[2] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                variable_[3] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                variable_[4] = HermesCalculator.reqQuShengAngle(float_array, 3, 5);
                variable_[5] = HermesCalculator.reqQuShengAngle(float_array, 4, 6);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    if (lineIndex <= 0 || lineIndex >= 15 * 60 * 60 * 100)
                    {
                        Console.WriteLine("准备阶段采集失败！");                                                                                     //需要改---
                        m_tipFlag = 1;                                                                                     //需要改---
                        m_tipContent = "准备阶段采集失败！";                                                                                     //需要改---
                        m_prepFlag = -1;                                                                                     //需要改---
                        m_jindutiao = 0;                                                                                     //需要改---
                        return;
                    }

                    Console.WriteLine("准备阶段采集完成！");                                                                                     //需要改--
                    m_tipFlag = 1;                                                                                     //需要改--
                    m_tipContent = "准备阶段采集完成！";                                                                                     //需要改--
                    m_prepFlag = 1;                                                                                     //需要改--
                    m_jindutiao = 0;                                                                                     //需要改--
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0 };                                                                                     //需要改--
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);    //需要改--
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1 && xiadunMin < -40 && variable_[0] > -15)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改--
                    m_tipFlag = 1;                                                                                     //需要改--
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改--
                    m_successFlag = 1;                                                                                      //需要改--
                    m_jindutiao = 1;
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析                                                                                                                      //需要改--
                    //上升时刻
                    if (m_hermesStateStablization_List[m_currentState + 1].isDownStage[0] == 1 && variable_[0] <= xiadunMin && variable_[0] < -15)
                    {
                        if (variable_[0] < -50)
                        {
                            //膝内扣角度 - 左
                            float angle1 = HermesCalculator.reqNeifanWaifanAngle4(float_array, 5, 3);
                            processAngleListList[m_currentState + 1, 0].Add(angle1);

                            //下蹲晃动-左
                            angle1 = HermesCalculator.reqNeifanWaifanAngle4(float_array, 5, 3);
                            processAngleListList[m_currentState + 1, 4].Add(angle1);
                        }

                        //下蹲幅度 - 左
                        float angle = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                        processAngleListList[m_currentState + 1, 2].Add(angle);
                       
                        //骨盆左右倾
                        angle = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 6].Add(angle);

                    }

                    if(HermesCalculator.reqAccMaxTotal(float_array, 5) > 1.7)
                    {
                        accCount += HermesCalculator.reqAccMaxTotal(float_array, 5);
                    }
                    if(accCount > 3 && xiadunMin < -80)
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的左脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的左脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = 1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        accCount = 2000;
                        return;
                    }
                    if (accCount > 3 && xiadunMin > -80)
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的左脚移动了\n请注意是左脚支撑，不是右脚支撑\n动作采集失败\n请点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的左脚移动了\n请注意是左脚支撑，不是右脚支撑\n动作采集失败\n请点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = -1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        return;
                    }
                    if (HermesCalculator.reqAccMaxTotal(float_array, 6) > 4.0)
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = 1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        accCount = 1000;
                        return;
                    }
                    
                }

                if (xiadunMin > variable_[0])
                {
                    xiadunMin = variable_[0];
                }

                //更新进度条-在期望区间时
                m_jindutiao = (float)xiadunMin / (float)-100;
                if (m_jindutiao > 1)
                {
                    m_jindutiao = 1;
                }
                else if (m_jindutiao < 0)
                {
                    m_jindutiao = 0;
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改--
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 50);                                                                                     //需要改--
            }
            else if (m_currentState == 1)                                                                                //需要改--
            {
               
            }

            if (m_successFlag == 1 && lineIndex % 100 == 0 && accCount <= 100)
            {
                Console.WriteLine("数据采集成功！");                                                                                     //需要改
                m_tipFlag = 1;                                                                                     //需要改
                m_tipContent = "数据采集成功！\n请点击下一个动作\n继续";
            }
            else if (m_successFlag == 1 && lineIndex % 100 == 0 && accCount > 3 && accCount == 2000)
            {
                Console.WriteLine("系统检测到您的左脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                              //需要改--
                m_tipFlag = 1;                                                                                     //需要改--
                m_tipContent = "系统检测到您的左脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";
            }
            else if (m_successFlag == -1 && lineIndex % 100 == 0 && accCount > 3 && accCount < 500)
            {
                Console.WriteLine("系统检测到您的左脚移动了\n请注意是左脚支撑，不是右脚支撑\n动作采集失败\n请点击小程序上的重试按钮重做");                                                                                     //需要改
                m_tipFlag = 1;                                                                                     //需要改
                m_tipContent = "系统检测到您的左脚移动了\n请注意是左脚支撑，不是右脚支撑\n动作采集失败\n请点击小程序上的重试按钮重做";
            }
            else if(m_successFlag == 1 && lineIndex % 100 == 0 && accCount == 1000)
            {
                Console.WriteLine("系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                m_tipFlag = 1;                                                                                     //需要改--
                m_tipContent = "系统检测到您的右脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if(m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
                
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();

            if (xiadunMin > -40)
            {
                //下蹲幅度 - 左
                ret.Add("30150", (float)-xiadunMin);
                return ret;
            }

            //左侧膝内扣  //左腿内扣为+，外扣为-，右腿外扣为+，内扣为-
            double[] list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 0], 0, processAngleListList[0 + 1, 0].Count() - 1);
            ret.Add("3001", (float)list[0]);
            Console.WriteLine("左侧膝内扣 " + (float)list[0]);

            //下蹲幅度 - 左    //-
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 2], 0, processAngleListList[0 + 1, 2].Count() - 1);
            ret.Add("30150", -(float)list[1]);
            Console.WriteLine("下蹲幅度 - 左 真" + ret["30150"]);

            if (accCount == 2000 || accCount == 1000)
            {
                //下蹲幅度 - 左
                ret["30150"] = (float)40;
                //return ret;
                Console.WriteLine("下蹲幅度 - 左 假" + ret["30150"]);
            }
            

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("YouCeDanTuiDun") == true)
            {
                if(HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].ContainsKey("30160") == true)
                {
                    float zuoce = ret["30150"];
                    float youce = HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"]["30160"];
                    //两侧下蹲幅度不同（左侧-右侧）
                    ret.Add("3015", zuoce - youce);
                    if (HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].ContainsKey("3016") == true)
                    {
                        //两侧下蹲幅度不同（右侧 - 左侧）
                        HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"]["3016"] = youce - zuoce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].Add("3016", youce - zuoce);
                    }
                }    
            }

            //下蹲晃动-左
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 4], 0, processAngleListList[0 + 1, 4].Count() - 1);   
            ret.Add("50010", (float)list[0] - (float)list[1]);
            Console.WriteLine("下蹲晃动-左 " + ((float)list[0] - (float)list[1]) + " " + (float)list[0] + " " + (float)list[1]);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("YouCeDanTuiDun") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].ContainsKey("50020") == true)
                {
                    float zuoce = ret["50010"];
                    float youce = HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"]["50020"];
                    //两侧下蹲晃动不同（左侧-右侧）
                    ret.Add("5001", zuoce - youce);
                    if (HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].ContainsKey("5002") == true)
                    {
                        //两侧下蹲晃动不同（右侧 - 左侧）
                        HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"]["5002"] = youce - zuoce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"].Add("5002", youce - zuoce);
                    }
                }
            }


            //骨盆左右倾  //骨盆左右摆动，向左-，向右+
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 6], 0, processAngleListList[0 + 1, 6].Count() - 1);   
            //骨盆左倾角度
            ret.Add("1001", -(float)list[1]);
            Console.WriteLine("骨盆左倾角度 " + -(float)list[1]);
            //骨盆右倾角度
            ret.Add("1002", (float)list[0]);
            Console.WriteLine("骨盆右倾角度 " + (float)list[0]);


            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoCeDanTuiDun") == true)
            {
                HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ZuoCeDanTuiDun", ret);
            }
            
            return ret;
        }


    }     //状态检测器-单腿蹲-左-旧版本，没有加速度积分

    public class HermesStateDetctorForYouCeDanTuiDun : HermesStateDetctor     //状态检测器-单腿蹲-右
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改---
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];
        //下蹲最大值
        public double xiadunMin;
        //加速度计数器
        double accCount;
        //加速度积分变量存储器-左脚
        public float[] accIntegralArrayLeft = new float[3];
        //加速度积分变量存储器-右脚
        public float[] accIntegralArrayRight = new float[3];

        //初始化函数
        public HermesStateDetctorForYouCeDanTuiDun()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            xiadunMin = 0;
            accCount = 0;
            accIntegralArrayLeft[0] = 0; accIntegralArrayLeft[1] = 0; accIntegralArrayLeft[2] = -1;
            accIntegralArrayRight[0] = 0; accIntegralArrayRight[1] = 0; accIntegralArrayRight[2] = -1;
            //准备阶段稳定器                                                                                     //需要改---
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedUp_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] expectedDown_ = new float[] { 15, 15, 15, 15, 15, 15 };
            float[] stableUp_ = new float[] { 3, 3, 3, 3, 3, 3 };
            float[] stableDown_ = new float[] { 3, 3, 3, 3, 3, 3 };
            int numOfVariable_ = 6;                                                                                 //需要改---
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改---
            preVariable_ = new float[] { 270 };
            expectedVariable_ = new float[] { 270 };
            expectedUp_ = new float[] { 10 };
            expectedDown_ = new float[] { 100 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;                                                                         //需要改---
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改---
                float[] variable_ = new float[] { 0, 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1);
                variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 0, 2);
                variable_[2] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                variable_[3] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                variable_[4] = HermesCalculator.reqQuShengAngle(float_array, 3, 5);
                variable_[5] = HermesCalculator.reqQuShengAngle(float_array, 4, 6);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    if(lineIndex <= 0 || lineIndex >= 15 * 60 * 60 * 100)
                    {
                        Console.WriteLine("准备阶段采集失败！");                                                                                     //需要改---
                        m_tipFlag = 1;                                                                                     //需要改---
                        m_tipContent = "准备阶段采集失败！";                                                                                     //需要改---
                        m_prepFlag = -1;                                                                                     //需要改---
                        m_jindutiao = 0;                                                                                     //需要改---
                        return;
                    }

                    Console.WriteLine("准备阶段采集完成！");                                                                                     //需要改---
                    m_tipFlag = 1;                                                                                     //需要改---
                    m_tipContent = "准备阶段采集完成！";                                                                                     //需要改---
                    m_prepFlag = 1;                                                                                     //需要改---
                    m_jindutiao = 0;                                                                                     //需要改---
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改--
                float[] variable_ = new float[] { 0 };                                                                                     //需要改---
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);    //需要改---
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1 && xiadunMin < -40 && variable_[0] > -15)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改---
                    m_tipFlag = 1;                                                                                     //需要改---
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改---
                    m_successFlag = 1;                                                                                      //需要改---
                    m_jindutiao = 1;
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析                                                                                                                      //需要改---
                    //上升时刻
                    if (m_hermesStateStablization_List[m_currentState + 1].isDownStage[0] == 1 && variable_[0] <= xiadunMin && variable_[0] < -15)
                    {
                        if(variable_[0] < -50)
                        {
                            //膝内扣角度 - 右
                            float angle1 = HermesCalculator.reqNeifanWaifanAngle4(float_array, 6, 4);
                            processAngleListList[m_currentState + 1, 0].Add(angle1);
                            //下蹲晃动-右
                            angle1 = HermesCalculator.reqNeifanWaifanAngle4(float_array, 6, 4);
                            processAngleListList[m_currentState + 1, 4].Add(angle1);
                        }

                        //下蹲幅度 - 右
                        float angle = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                        processAngleListList[m_currentState + 1, 2].Add(angle);
                        
                        //骨盆左右倾
                        angle = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 0, 0);
                        processAngleListList[m_currentState + 1, 6].Add(angle);
                    }

                    //更新加速度积分
                    float[] distanceLeft = HermesCalculator.reqAccToDistance(float_array, 5, accIntegralArrayLeft[0], accIntegralArrayLeft[1], (int)accIntegralArrayLeft[2], lineIndex);
                    accIntegralArrayLeft[0] = distanceLeft[0];
                    accIntegralArrayLeft[1] = distanceLeft[1];
                    accIntegralArrayLeft[2] = distanceLeft[2];
                    float[] distanceRight = HermesCalculator.reqAccToDistance(float_array, 6, accIntegralArrayRight[0], accIntegralArrayRight[1], (int)accIntegralArrayRight[2], lineIndex);
                    accIntegralArrayRight[0] = distanceRight[0];
                    accIntegralArrayRight[1] = distanceRight[1];
                    accIntegralArrayRight[2] = distanceRight[2];

                    if (HermesCalculator.reqAccMaxTotal(float_array, 6) > 1.6)
                    {
                        accCount += HermesCalculator.reqAccMaxTotal(float_array, 6);
                    }

                    if (((Math.Abs(accIntegralArrayLeft[0]) < Math.Abs(accIntegralArrayRight[0])) || accCount > 15) && xiadunMin < -60)
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的右脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的右脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = 1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        accCount = 2000;
                        return;
                    }
                    if (((Math.Abs(accIntegralArrayLeft[0]) < Math.Abs(accIntegralArrayRight[0])) || accCount > 3) && xiadunMin > -60)
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的右脚移动了\n请注意是右脚支撑下蹲\n不是左脚\n动作采集失败\n请点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的右脚移动了\n请注意是右脚支撑下蹲\n不是左脚\n动作采集失败\n请点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = -1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        return;
                    }
                    if (HermesCalculator.reqAccMaxTotal(float_array, 5) > 3.0 && xiadunMin < -60)
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的左脚\n在动作中晃动剧烈或者接触地面\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的左脚\n在动作中晃动剧烈或者接触地面\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = 1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        accCount = 1000;
                        return;
                    }
                    if (HermesCalculator.reqAccMaxTotal(float_array, 5) > 3.0 && xiadunMin > -60)
                    {
                        m_currentState = 1;
                        Console.WriteLine("系统检测到您的左脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                        m_tipFlag = 1;                                                                                     //需要改--
                        m_tipContent = "系统检测到您的左脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";                                                                                     //需要改--
                        m_successFlag = 1;                                                                                      //需要改--
                        m_jindutiao = 0;
                        accCount = 3000;
                        return;
                    }
                }

                if (xiadunMin > variable_[0])
                {
                    xiadunMin = variable_[0];
                }

                //更新进度条-在期望区间时
                m_jindutiao = (float)xiadunMin / (float)-100;
                if (m_jindutiao > 1)
                {
                    m_jindutiao = 1;
                }
                else if (m_jindutiao < 0)
                {
                    m_jindutiao = 0;
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改---
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 50);                                                                                     //需要改---
            }
            else if (m_currentState == 1)                                                                                //需要改---
            {

            }

            if (m_successFlag == 1 && lineIndex % 100 == 0 && accCount <= 100)
            {
                Console.WriteLine("数据采集成功！");                                                                                     //需要改
                m_tipFlag = 1;                                                                                     //需要改
                m_tipContent = "数据采集成功！\n请点击下一个动作\n继续";
            }
            else if (m_successFlag == 1 && lineIndex % 100 == 0 && accCount > 3 && accCount == 2000)
            {
                Console.WriteLine("系统检测到您的右脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                              //需要改--
                m_tipFlag = 1;                                                                                     //需要改--
                m_tipContent = "系统检测到您的右脚移动了\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";
            }
            else if (m_successFlag == -1 && lineIndex % 100 == 0 && accCount > 3 && accCount < 500)
            {
                Console.WriteLine("系统检测到您的右脚移动了\n请注意是右脚支撑下蹲\n不是左脚\n动作采集失败\n请点击小程序上的重试按钮重做");                                                                                     //需要改
                m_tipFlag = 1;                                                                                     //需要改
                m_tipContent = "系统检测到您的右脚移动了\n请注意是右脚支撑下蹲\n不是左脚\n动作采集失败\n请点击小程序上的重试按钮重做";
            }
            else if (m_successFlag == 1 && lineIndex % 100 == 0 && accCount == 1000)
            {
                Console.WriteLine("系统检测到您的左脚\n在动作中晃动剧烈或者接触地面\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                m_tipFlag = 1;                                                                                     //需要改--
                m_tipContent = "系统检测到您的左脚\n在动作中晃动剧烈或者接触地面\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";
            }
            else if (m_successFlag == 1 && lineIndex % 100 == 0 && accCount == 3000)
            {
                Console.WriteLine("系统检测到您的左脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做");                                                                                     //需要改--
                m_tipFlag = 1;                                                                                     //需要改--
                m_tipContent = "系统检测到您的左脚\n在动作中晃动剧烈或者接触地面\n无法顺利站起\n动作已经采集完成\n请点击小程序上的下一个按钮继续\n也可以点击小程序上的重试按钮重做";
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "数据采集失败，\n请点击重做动作\n重做测试";
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改---
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();

            if(xiadunMin > -40)
            {
                //下蹲幅度 - 右
                ret.Add("30160", -(float)xiadunMin);
                return ret;
            }

            //右侧膝内扣
            double[] list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 0], 0, processAngleListList[0 + 1, 0].Count() - 1);
            ret.Add("3002", -(float)list[1]);
            Console.WriteLine("右侧膝内扣 " + -(float)list[1]);

            //下蹲幅度 - 右
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 2], 0, processAngleListList[0 + 1, 2].Count() - 1);
            ret.Add("30160", -(float)list[1]);
            Console.WriteLine("下蹲幅度 - 右 真" + ret["30160"]);

            if (accCount == 2000 || accCount == 1000 || accCount == 3000)
            {
                //下蹲幅度 - 左
                ret["30160"] = (float)40;
                //return ret;
                Console.WriteLine("下蹲幅度 - 右 假" + ret["30160"]);
            }

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoCeDanTuiDun") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"].ContainsKey("30150") == true)
                {
                    float zuoce = HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"]["30150"];
                    float youce = ret["30160"];
                    //两侧下蹲幅度不同（左侧-右侧）
                    ret.Add("3016", youce - zuoce);
                    if (HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"].ContainsKey("3015") == true)
                    {
                        //两侧下蹲幅度不同（右侧 - 左侧）
                        HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"]["3015"] = zuoce - youce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"].Add("3015", zuoce - youce);
                    }
                }
            }

            //下蹲晃动-左
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 4], 0, processAngleListList[0 + 1, 4].Count() - 1);
            ret.Add("50020", (float)list[0] - (float)list[1]);
            Console.WriteLine("下蹲晃动-左 " + ((float)list[0] - (float)list[1]));

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoCeDanTuiDun") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"].ContainsKey("50010") == true)
                {
                    float zuoce = HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"]["50010"];
                    float youce = ret["50020"];
                    //两侧下蹲晃动不同（左侧-右侧）
                    ret.Add("5002", youce - zuoce);
                    if (HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"].ContainsKey("5001") == true)
                    {
                        //两侧下蹲晃动不同（右侧 - 左侧）
                        HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"]["5001"] = zuoce - youce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["ZuoCeDanTuiDun"].Add("5001", zuoce - youce);
                    }
                }
            }


            //骨盆左右倾
            list = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 6], 0, processAngleListList[0 + 1, 6].Count() - 1);
            //骨盆左倾角度
            ret.Add("1001", -(float)list[1]);
            Console.WriteLine("骨盆左倾角度 " + (float)list[1]);
            //骨盆右倾角度
            ret.Add("1002", (float)list[0]);
            Console.WriteLine("骨盆右倾角度 " + (float)list[0]);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("YouCeDanTuiDun") == true)
            {
                HermesNewTest.m_tezhengDic_all["YouCeDanTuiDun"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("YouCeDanTuiDun", ret);
            }

            return ret;
        }


    }     //状态检测器-单腿蹲-右

    public class HermesStateDetctorForShuangShouZuoCeDanTuiFuQiao : HermesStateDetctor     //状态检测器-双手左侧单腿腹桥
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改----
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForShuangShouZuoCeDanTuiFuQiao()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改----
            float[] preVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedUp_ = new float[] { 35, 35, 35, 35, 35 };
            float[] expectedDown_ = new float[] { 30, 25, 25, 25, 25 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 }  ;
            int numOfVariable_ = 5;                                                                        //需要改----
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改----
            preVariable_ = new float[] { 250 };
            expectedVariable_ = new float[] { 250 };
            expectedUp_ = new float[] { 10 };
            expectedDown_ = new float[] { 10 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;                                                                         //需要改----
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改----
                float[] variable_ = new float[] { 0, 0, 0, 0, 0};
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);

                m_variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                m_variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                m_variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                m_variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                m_variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_variable_[8] = m_hermesStateStablization_List[m_currentState + 1].stableTime;

                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    if (lineIndex <= 0 || lineIndex >= 15 * 60 * 60 * 100)
                    {
                        Console.WriteLine("准备阶段采集失败！");                                                                                     //需要改---
                        m_tipFlag = 1;                                                                                     //需要改---
                        m_tipContent = "准备阶段采集失败！";                                                                                     //需要改---
                        m_prepFlag = -1;                                                                                     //需要改---
                        m_jindutiao = 0;                                                                                     //需要改---
                        return;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！" + variable_[0] + ' ' + variable_[1] + ' ' + variable_[2] + ' ' + variable_[3] + ' ' + variable_[4] + ' ');                                                                                     //需要改----
                    m_tipFlag = 1;                                                                                     //需要改----
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改----
                    m_prepFlag = 1;                                                                                     //需要改----
                    m_jindutiao = 0;                                                                                     //需要改----
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改---
                float[] variable_ = new float[] { 0 };                                                                                     //需要改----
                variable_[0] = HermesCalculator.reqPaziWaizhan2(float_array, 0, 3) - HermesCalculator.reqPaziWaizhan2(stageEndStateList[0], 0, 3);    //需要改----
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改----
                    m_tipFlag = 1;                                                                                     //需要改----
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改----
                    //m_successFlag = 1;                                                                                      //需要改----
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 0)    //需要改----
                {
                    //过程分析                                                                                                                      //需要改----
                    //任何时刻
                    //小腿夹角
                    float angle = HermesCalculator.reqPaziWaizhan2(float_array, 0, 3) - HermesCalculator.reqPaziWaizhan2(stageEndStateList[0], 0, 3); ;
                    processAngleListList[m_currentState + 1, 0].Add(angle);
                    //左大腿抬起角度
                    angle = HermesCalculator.reqPaziTuibuQuShengAngleToGround(float_array, 0, 1);
                    processAngleListList[m_currentState + 1, 1].Add(angle);
                    //右大腿抬起角度
                    angle = HermesCalculator.reqPaziTuibuQuShengAngleToGround(float_array, 0, 2);
                    processAngleListList[m_currentState + 1, 2].Add(angle);
                    //骨盆前后倾
                    angle = HermesCalculator.reqPaziYaobuQuShengAngleToGround(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 3].Add(angle);
                    //骨盆前旋转
                    angle = HermesCalculator.reqPaziYaobuZXuanzhuan(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 4].Add(angle);
                    //骨盆左右倾
                    angle = HermesCalculator.reqPaziYaobuZuoyouxuanzhuan(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 5].Add(angle);
                }

                if(lineIndex % 30 == 0)
                {
                    List<double> xiaotuijiajiao_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 0, 26);
                    List<int> xiaotuijiajiao_min = HermesCalculator.huaxianValueUpOnlyOneTime(xiaotuijiajiao_pinhua, 20, 20, 26);
                    motionCount = xiaotuijiajiao_min.Count;

                    Console.WriteLine("第一阶段采集完成！数量：" + motionCount);

                    if (motionCount >= 3)
                    {
                        m_currentState = 1;
                        Console.WriteLine("第一阶段采集完成！数量");                                                                                     //需要改----
                        m_tipFlag = 1;                                                                                     //需要改----
                        m_tipContent = "动作采集完成！";                                                                                     //需要改----   
                        m_successFlag = 1;
                        m_jindutiao = 1;
                        return;
                    }
                }

                //更新进度条-在期望区间时
                m_jindutiao = (float)motionCount / (float)3;
                if (m_jindutiao > 1)
                {
                    m_jindutiao = 1;
                }
                else if (m_jindutiao < 0)
                {
                    m_jindutiao = 0;
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 150);                                                                                     //需要改----
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 300);                                                                                     //需要改----
            }
            else if (m_currentState == 1)                                                                                //需要改----
            {

            }

            if (m_successFlag == 1 && lineIndex % 100 == 0)
            {
                Console.WriteLine("数据采集成功！");                                                                                     //需要改
                m_tipFlag = 1;                                                                                     //需要改
                m_tipContent = "数据采集成功！\n请点击下一个动作\n继续";
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "数据采集失败，\n请点击重做动作\n重做测试";
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改---
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();

            //左
            //求两个小腿的夹角最大值-左
            List<double> xiaotuijiajiao_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 0, 26);
            List<int> xiaotuijiajiao_min = HermesCalculator.huaxianValueUpOnlyOneTime(xiaotuijiajiao_pinhua, 20, 20, 26);
            HermesCalculator.printList(xiaotuijiajiao_min, "两个小腿的夹角最大值");
            List<double> xiaotuijiajiao_min_value_List = new List<double>();
            for (int i = 0; i < xiaotuijiajiao_min.Count; i++)
            {
                xiaotuijiajiao_min_value_List.Add(processAngleListList[1, 0][xiaotuijiajiao_min[i]]);
            }
            HermesCalculator.printListDouble(xiaotuijiajiao_min_value_List, "两个小腿的夹角最大值");

            if (xiaotuijiajiao_min.Count < 2)
            {
                return ret;
            }

            //左侧最大打开角度
            double[] maxDatuiJiajiao = HermesCalculator.calMaxMinMeanVar(xiaotuijiajiao_min_value_List, 0, xiaotuijiajiao_min_value_List.Count - 1);
            ret.Add("20260", (float)maxDatuiJiajiao[0]);

            //伸髋不足，大腿掉落 - 左
            List<double> angleListTotal = new List<double>();
            List<double> angleList = new List<double>();
            for (int i = 0; i < xiaotuijiajiao_min.Count(); i++)
            {
                angleList.Add(processAngleListList[1, 1][xiaotuijiajiao_min[i]]);
                angleListTotal.Add(processAngleListList[1, 1][xiaotuijiajiao_min[i]]);
            }
            HermesCalculator.printListDouble(angleList, "伸髋不足，大腿掉落 - 左");

            List<double> angleMaxList = new List<double>();
            List<double> angleMinList = new List<double>();
            for (int i = 0; i < xiaotuijiajiao_min.Count()-1; i++)
            {
                double[] xxx = HermesCalculator.calMaxMinMeanVar(processAngleListList[1, 1], xiaotuijiajiao_min[i], xiaotuijiajiao_min[i + 1]);
                angleMaxList.Add(xxx[0]);
                angleMinList.Add(xxx[1]);
                angleListTotal.Add(xxx[0]);
                angleListTotal.Add(xxx[1]);
            }
            HermesCalculator.printListDouble(angleMaxList, "数值最大值 - 左");
            HermesCalculator.printListDouble(angleMinList, "数值最小值 - 左");

            HermesCalculator.printListDouble(angleListTotal, "伸髋不足，大腿掉落 总 - 左");

            double[] maxMin = HermesCalculator.calMaxMinMeanVar(angleListTotal, 0, angleListTotal.Count-1);

            ret.Add("2026", -(float)maxMin[1] + 90);
            Console.WriteLine("2026： " + (-(float)maxMin[1] + 90));

            //骨盆掉落
            //骨盆前后倾
            List<double> gupengqianhouqin_MaxList = new List<double>();
            List<double> gupengqianhouqin_MinList = new List<double>();
            //骨盆左右倾
            List<double> gupengzuoyouqin_MaxList = new List<double>();
            List<double> gupengzuoyouqin_MinList = new List<double>();
            //骨盆旋转
            List<double> gupengxuanzhuan_MaxList = new List<double>();
            List<double> gupengxuanzhuan_MinList = new List<double>();
            for (int i = 0; i < xiaotuijiajiao_min.Count() - 1; i++)
            {
                double[] xxx = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 3], xiaotuijiajiao_min[i], xiaotuijiajiao_min[i + 1]);
                gupengqianhouqin_MaxList.Add(xxx[0]);
                gupengqianhouqin_MinList.Add(xxx[1]);
                xxx = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 5], xiaotuijiajiao_min[i], xiaotuijiajiao_min[i + 1]);
                gupengzuoyouqin_MaxList.Add(xxx[0]);
                gupengzuoyouqin_MinList.Add(xxx[1]);
                xxx = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 4], xiaotuijiajiao_min[i], xiaotuijiajiao_min[i + 1]);
                gupengxuanzhuan_MaxList.Add(xxx[0]);
                gupengxuanzhuan_MinList.Add(xxx[1]);
            }

            HermesCalculator.printListDouble(gupengqianhouqin_MaxList, "骨盆前后倾 - 最大值 - 左");
            HermesCalculator.printListDouble(gupengqianhouqin_MinList, "骨盆前后倾 - 最小值 - 左");
            HermesCalculator.printListDouble(gupengzuoyouqin_MaxList, "骨盆左右倾 - 最大值 - 左");
            HermesCalculator.printListDouble(gupengzuoyouqin_MinList, "骨盆左右倾 - 最小值 - 左");
            HermesCalculator.printListDouble(gupengxuanzhuan_MaxList, "骨盆旋转 - 最大值 - 左");
            HermesCalculator.printListDouble(gupengxuanzhuan_MinList, "骨盆旋转 - 最小值 - 左");

            double absmax = 0;
            //左右倾平均值再取最大值
            double[] meanValue = HermesCalculator.calMaxMinMeanVar(gupengzuoyouqin_MaxList, 0, gupengzuoyouqin_MaxList.Count - 1);
            float resultValue = ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZuoyouxuanzhuan(stageEndStateList[0], 0, 0));
            Console.WriteLine("骨盆左右倾 - 最大值-平均值： " + ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZuoyouxuanzhuan(stageEndStateList[0], 0, 0)));
            if (Math.Abs(resultValue) > absmax) absmax = Math.Abs(resultValue);
            //左右倾平均值再取最小值
            meanValue = HermesCalculator.calMaxMinMeanVar(gupengzuoyouqin_MinList, 0, gupengzuoyouqin_MinList.Count - 1);
            resultValue = ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZuoyouxuanzhuan(stageEndStateList[0], 0, 0));
            Console.WriteLine("骨盆左右倾 - 最小值-平均值： " + ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZuoyouxuanzhuan(stageEndStateList[0], 0, 0)));
            if (Math.Abs(resultValue) > absmax) absmax = Math.Abs(resultValue);
            //旋转平均值再取最大值
            meanValue = HermesCalculator.calMaxMinMeanVar(gupengxuanzhuan_MaxList, 0, gupengxuanzhuan_MaxList.Count - 1);
            resultValue = ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[0], 0, 0));
            Console.WriteLine("骨盆旋转 - 最大值-平均值： " + ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[0], 0, 0)));
            if (Math.Abs(resultValue) > absmax) absmax = Math.Abs(resultValue);
            //旋转平均值再取最小值
            meanValue = HermesCalculator.calMaxMinMeanVar(gupengxuanzhuan_MinList, 0, gupengxuanzhuan_MinList.Count - 1);
            resultValue = ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[0], 0, 0));
            Console.WriteLine("骨盆旋转 - 最小值-平均值： " + ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[0], 0, 0)));
            if (Math.Abs(resultValue) > absmax) absmax = Math.Abs(resultValue);

            ret.Add("1007", (float)absmax);
            Console.WriteLine("1007： " + (float)absmax);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ShuangShouZuoCeDanTuiFuQiao") == true)
            {
                HermesNewTest.m_tezhengDic_all["ShuangShouZuoCeDanTuiFuQiao"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ShuangShouZuoCeDanTuiFuQiao", ret);
            }

            return ret;
        }


    }     //状态检测器-双手左侧单腿腹桥

    public class HermesStateDetctorForShuangShouYouCeDanTuiFuQiao : HermesStateDetctor     //状态检测器-双手右侧单腿腹桥
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改----
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];
        int motionCount;

        //初始化函数
        public HermesStateDetctorForShuangShouYouCeDanTuiFuQiao()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改----
            float[] preVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedUp_ = new float[] { 35, 35, 35, 35, 35 };
            float[] expectedDown_ = new float[] { 30, 25, 25, 25, 25 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改----
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改----
            preVariable_ = new float[] { 250 };
            expectedVariable_ = new float[] { 250 };
            expectedUp_ = new float[] { 10 };
            expectedDown_ = new float[] { 10 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;                                                                         //需要改----
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改----
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    if (lineIndex <= 0 || lineIndex >= 15 * 60 * 60 * 100)
                    {
                        Console.WriteLine("准备阶段采集失败！");                                                                                     //需要改---
                        m_tipFlag = 1;                                                                                     //需要改---
                        m_tipContent = "准备阶段采集失败！";                                                                                     //需要改---
                        m_prepFlag = -1;                                                                                     //需要改---
                        m_jindutiao = 0;                                                                                     //需要改---
                        return;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！" + variable_[0] + ' ' + variable_[1] + ' ' + variable_[2] + ' ' + variable_[3] + ' ' + variable_[4] + ' ');                                                                                     //需要改----
                    m_tipFlag = 1;                                                                                     //需要改----
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改----
                    m_prepFlag = 1;                                                                                     //需要改----
                    m_jindutiao = 0;                                                                                     //需要改----
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改---
                float[] variable_ = new float[] { 0 };                                                                                     //需要改----
                variable_[0] = HermesCalculator.reqPaziWaizhan2(float_array, 0, 4) - HermesCalculator.reqPaziWaizhan2(stageEndStateList[0], 0, 4);    //需要改----
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改----
                    m_tipFlag = 1;                                                                                     //需要改----
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改----
                    //m_successFlag = 1;                                                                                      //需要改----
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 0)    //需要改----
                {
                    //过程分析                                                                                                                      //需要改----
                    //任何时刻
                    //小腿夹角
                    float angle = HermesCalculator.reqPaziWaizhan2(float_array, 0, 4) - HermesCalculator.reqPaziWaizhan2(stageEndStateList[0], 0, 4); ;
                    processAngleListList[m_currentState + 1, 0].Add(angle);
                    //左大腿抬起角度
                    angle = HermesCalculator.reqPaziTuibuQuShengAngleToGround(float_array, 0, 2);
                    processAngleListList[m_currentState + 1, 1].Add(angle);
                    //右大腿抬起角度
                    angle = HermesCalculator.reqPaziTuibuQuShengAngleToGround(float_array, 0, 1);
                    processAngleListList[m_currentState + 1, 2].Add(angle);
                    //骨盆前后倾
                    angle = HermesCalculator.reqPaziYaobuQuShengAngleToGround(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 3].Add(angle);
                    //骨盆前旋转
                    angle = HermesCalculator.reqPaziYaobuZXuanzhuan(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 4].Add(angle);
                    //骨盆左右倾
                    angle = HermesCalculator.reqPaziYaobuZuoyouxuanzhuan(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 5].Add(angle);
                }

                if (lineIndex % 60 == 0)
                {
                    List<double> xiaotuijiajiao_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 0, 26);
                    List<int> xiaotuijiajiao_min = HermesCalculator.huaxianValueDownOnlyOneTime(xiaotuijiajiao_pinhua, -20, -20, 26);
                    motionCount = xiaotuijiajiao_min.Count;

                    Console.WriteLine("第一阶段采集完成！数量：" + motionCount);

                    if (motionCount >= 3)
                    {
                        m_currentState = 1;
                        Console.WriteLine("第一阶段采集完成！数量");                                                                                     //需要改----
                        m_tipFlag = 1;                                                                                     //需要改----
                        m_tipContent = "动作采集完成！";                                                                                     //需要改----   
                        m_successFlag = 1;
                        m_jindutiao = 1;
                        return;
                    }
                }

                //更新进度条-在期望区间时
                m_jindutiao = (float)motionCount / (float)3;
                if (m_jindutiao > 1)
                {
                    m_jindutiao = 1;
                }
                else if (m_jindutiao < 0)
                {
                    m_jindutiao = 0;
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 150);                                                                                     //需要改----
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 300);                                                                                     //需要改----
            }
            else if (m_currentState == 1)                                                                                //需要改----
            {

            }

            if (m_successFlag == 1 && lineIndex % 100 == 0)
            {
                Console.WriteLine("数据采集成功！");                                                                                     //需要改
                m_tipFlag = 1;                                                                                     //需要改
                m_tipContent = "数据采集成功！\n请点击下一个动作\n继续";
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "数据采集失败，\n请点击重做动作\n重做测试";
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改---
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();

            //右
            //求两个小腿的夹角最小值-右
            List<double> xiaotuijiajiao_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 0, 26);
            List<int> xiaotuijiajiao_min = HermesCalculator.huaxianValueDownOnlyOneTime(xiaotuijiajiao_pinhua, -20, -20, 26);
            HermesCalculator.printList(xiaotuijiajiao_min, "两个小腿的夹角最小值序号");
            List<double> xiaotuijiajiao_min_value_List = new List<double>();
            for (int i = 0; i < xiaotuijiajiao_min.Count; i++)
            {
                xiaotuijiajiao_min_value_List.Add(processAngleListList[1, 0][xiaotuijiajiao_min[i]]);
            }
            HermesCalculator.printListDouble(xiaotuijiajiao_min_value_List, "两个小腿的夹角最小值");

            if (xiaotuijiajiao_min.Count < 2)
            {
                return ret;
            }

            //右侧最大打开角度
            double[] maxDatuiJiajiao = HermesCalculator.calMaxMinMeanVar(xiaotuijiajiao_min_value_List, 0, xiaotuijiajiao_min_value_List.Count - 1);
            ret.Add("20270", -(float)maxDatuiJiajiao[1]);

            //伸髋不足，大腿掉落 - 右
            List<double> angleListTotal = new List<double>();
            List<double> angleList = new List<double>();
            for (int i = 0; i < xiaotuijiajiao_min.Count(); i++)
            {
                angleList.Add(processAngleListList[1, 1][xiaotuijiajiao_min[i]]);
                angleListTotal.Add(processAngleListList[1, 1][xiaotuijiajiao_min[i]]);
            }
            HermesCalculator.printListDouble(angleList, "伸髋不足，大腿掉落 - 右");

            List<double> angleMaxList = new List<double>();
            List<double> angleMinList = new List<double>();
            for (int i = 0; i < xiaotuijiajiao_min.Count() - 1; i++)
            {
                double[] xxx = HermesCalculator.calMaxMinMeanVar(processAngleListList[1, 1], xiaotuijiajiao_min[i], xiaotuijiajiao_min[i + 1]);
                angleMaxList.Add(xxx[0]);
                angleMinList.Add(xxx[1]);
                angleListTotal.Add(xxx[0]);
                angleListTotal.Add(xxx[1]);
            }
            HermesCalculator.printListDouble(angleMaxList, "数值最大值 - 右");
            HermesCalculator.printListDouble(angleMinList, "数值最小值 - 右");

            HermesCalculator.printListDouble(angleListTotal, "伸髋不足，大腿掉落 总 - 右");

            double[] maxMin = HermesCalculator.calMaxMinMeanVar(angleListTotal, 0, angleListTotal.Count - 1);

            ret.Add("2027", -(float)maxMin[1] + 90);
            Console.WriteLine("2027： " + (-(float)maxMin[1] + 90));

            //骨盆掉落
            //骨盆前后倾
            List<double> gupengqianhouqin_MaxList = new List<double>();
            List<double> gupengqianhouqin_MinList = new List<double>();
            //骨盆左右倾
            List<double> gupengzuoyouqin_MaxList = new List<double>();
            List<double> gupengzuoyouqin_MinList = new List<double>();
            //骨盆旋转
            List<double> gupengxuanzhuan_MaxList = new List<double>();
            List<double> gupengxuanzhuan_MinList = new List<double>();
            for (int i = 0; i < xiaotuijiajiao_min.Count() - 1; i++)
            {
                double[] xxx = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 3], xiaotuijiajiao_min[i], xiaotuijiajiao_min[i + 1]);
                gupengqianhouqin_MaxList.Add(xxx[0]);
                gupengqianhouqin_MinList.Add(xxx[1]);
                xxx = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 5], xiaotuijiajiao_min[i], xiaotuijiajiao_min[i + 1]);
                gupengzuoyouqin_MaxList.Add(xxx[0]);
                gupengzuoyouqin_MinList.Add(xxx[1]);
                xxx = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 4], xiaotuijiajiao_min[i], xiaotuijiajiao_min[i + 1]);
                gupengxuanzhuan_MaxList.Add(xxx[0]);
                gupengxuanzhuan_MinList.Add(xxx[1]);
            }

            HermesCalculator.printListDouble(gupengqianhouqin_MaxList, "骨盆前后倾 - 最大值 - 右");
            HermesCalculator.printListDouble(gupengqianhouqin_MinList, "骨盆前后倾 - 最小值 - 右");
            HermesCalculator.printListDouble(gupengzuoyouqin_MaxList, "骨盆左右倾 - 最大值 - 右");
            HermesCalculator.printListDouble(gupengzuoyouqin_MinList, "骨盆左右倾 - 最小值 - 右");
            HermesCalculator.printListDouble(gupengxuanzhuan_MaxList, "骨盆旋转 - 最大值 - 右");
            HermesCalculator.printListDouble(gupengxuanzhuan_MinList, "骨盆旋转 - 最小值 - 右");

            double absmax = 0;
            //前后倾平均值再取最大值
            double[] meanValue = HermesCalculator.calMaxMinMeanVar(gupengzuoyouqin_MaxList, 0, gupengzuoyouqin_MaxList.Count - 1);
            float resultValue = ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZuoyouxuanzhuan(stageEndStateList[0], 0, 0));
            Console.WriteLine("骨盆左右倾 - 最大值-平均值： " + ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZuoyouxuanzhuan(stageEndStateList[0], 0, 0)));
            if (Math.Abs(resultValue) > absmax) absmax = Math.Abs(resultValue);
            //前后倾平均值再取最小值
            meanValue = HermesCalculator.calMaxMinMeanVar(gupengzuoyouqin_MinList, 0, gupengzuoyouqin_MinList.Count - 1);
            resultValue = ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZuoyouxuanzhuan(stageEndStateList[0], 0, 0));
            Console.WriteLine("骨盆左右倾 - 最小值-平均值： " + ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZuoyouxuanzhuan(stageEndStateList[0], 0, 0)));
            if (Math.Abs(resultValue) > absmax) absmax = Math.Abs(resultValue);
            //前后倾平均值再取最大值
            meanValue = HermesCalculator.calMaxMinMeanVar(gupengxuanzhuan_MaxList, 0, gupengxuanzhuan_MaxList.Count - 1);
            resultValue = ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[0], 0, 0));
            Console.WriteLine("骨盆旋转 - 最大值-平均值： " + ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[0], 0, 0)));
            if (Math.Abs(resultValue) > absmax) absmax = Math.Abs(resultValue);
            //前后倾平均值再取最小值
            meanValue = HermesCalculator.calMaxMinMeanVar(gupengxuanzhuan_MinList, 0, gupengxuanzhuan_MinList.Count - 1);
            resultValue = ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[0], 0, 0));
            Console.WriteLine("骨盆旋转 - 最小值-平均值： " + ((float)meanValue[2] - HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[0], 0, 0)));
            if (Math.Abs(resultValue) > absmax) absmax = Math.Abs(resultValue);

            ret.Add("1008", (float)absmax);
            Console.WriteLine("1008： " + (float)absmax);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ShuangShouYouCeDanTuiFuQiao") == true)
            {
                HermesNewTest.m_tezhengDic_all["ShuangShouYouCeDanTuiFuQiao"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ShuangShouYouCeDanTuiFuQiao", ret);
            }

            return ret;
        }


    }     //状态检测器-双手右侧单腿腹桥

    public class HermesStateDetctorForZuoCeDanJiaoZhiCheng : HermesStateDetctor     //状态检测器-左侧单脚支撑
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改
        public float[][] stageEndStateList = new float[stageNum+8][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum + 8, 12];
        public int moveInCount;
        int moveInFlag;

        //初始化函数
        public HermesStateDetctorForZuoCeDanJiaoZhiCheng()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            moveInCount = -1;
            moveInFlag = 0;
            //准备阶段稳定器                                                                                     //需要改
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedUp_ = new float[] { 15, 15, 20, 20, 20, 20 };
            float[] expectedDown_ = new float[] { 15, 15, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 7, 7, 7, 7, 7, 7 };
            float[] stableDown_ = new float[] { 7, 7, 7, 7, 7, 7 };
            int numOfVariable_ = 6;                                                                        //需要改
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改
            preVariable_ = new float[] { 250, 250 };
            expectedVariable_ = new float[] { 250 , 250 };
            expectedUp_ = new float[] { 10, 10 };
            expectedDown_ = new float[] { 10, 10 };
            stableUp_ = new float[] { 30, 40 };
            stableDown_ = new float[] { 35, 20 };
            numOfVariable_ = 2;                                                                         //需要改
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum + 8; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 12; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改
                float[] variable_ = new float[] { 0, 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1); 
                variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 0, 2);
                variable_[2] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                variable_[3] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                variable_[4] = HermesCalculator.reqQuShengAngle(float_array, 3, 5);
                variable_[5] = HermesCalculator.reqQuShengAngle(float_array, 4, 6);

                m_variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1);
                m_variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 0, 2);
                m_variable_[2] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                m_variable_[3] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                m_variable_[4] = HermesCalculator.reqQuShengAngle(float_array, 3, 5);
                m_variable_[5] = HermesCalculator.reqQuShengAngle(float_array, 4, 6);
                m_variable_[8] = m_hermesStateStablization_List[m_currentState + 1].stableTime;

                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    if (lineIndex <= 0 || lineIndex >= 15 * 60 * 60 * 100)
                    {
                        Console.WriteLine("准备阶段采集失败！");                                                                                     //需要改---
                        m_tipFlag = 1;                                                                                     //需要改---
                        m_tipContent = "准备阶段采集失败！";                                                                                     //需要改---
                        m_prepFlag = -1;                                                                                     //需要改---
                        m_jindutiao = 0;                                                                                     //需要改---
                        return;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改
                    m_prepFlag = 1;                                                                                     //需要改
                    m_jindutiao = 0;                                                                                     //需要改
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改---
                float[] variable_ = new float[] { 0, 0 };                                                                                     //需要改
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);                                   //需要改
                variable_[1] = HermesCalculator.reqQuShengAngleToGround(float_array, 0, 2);                                       //需要改
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值10次，超过10次算超时
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime  &&  m_hermesStateStablization_List[m_currentState + 1].stableTime <= 100*20
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1 && m_hermesStateStablization_List[m_currentState + 1].stablizedVariable[0] < -40 )
                {
                    //保存数据
                    if(m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime)
                    {
                        if(moveInFlag == 0)
                        {
                            moveInCount++;
                            moveInFlag = 1;
                        }
                    }
                    if(moveInCount >=0 && moveInCount < 9) {
                        //记录时间数据
                        processAngleListList[m_currentState + 1, moveInCount].Add(lineIndex);
                        //腰部前后倾
                        float yaobu_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 0, 0);
                        processAngleListList[m_currentState + 2, moveInCount].Add(yaobu_x);
                        //腰部旋转
                        float yaobu_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 0, 0);
                        processAngleListList[m_currentState + 3, moveInCount].Add(yaobu_z);
                        //左右摆动，向左-，向右+
                        float yaobu_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 0, 0);
                        processAngleListList[m_currentState + 4, moveInCount].Add(yaobu_y);
                        //左脚部前后倾
                        float jiao_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 5, 5);
                        processAngleListList[m_currentState + 5, moveInCount].Add(jiao_x);
                        //左脚部旋转
                        float jiao_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 5, 5);
                        processAngleListList[m_currentState + 6, moveInCount].Add(jiao_z);
                        //左脚部左右摆动，向左-，向右+
                        float jiao_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 5, 5);
                        processAngleListList[m_currentState + 7, moveInCount].Add(jiao_y);
                    }
                    else if(moveInCount >= 9)
                    {
                        //跳出，进入下一阶段
                        m_currentState = 1;
                        Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改
                        m_tipFlag = 1;                                                                                     //需要改
                        m_tipContent = "动作采集完成\n您可以进入下一个动作！";                                                                                     //需要改
                        m_successFlag = 1;
                        return;
                    }
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 0)    //需要改
                {
                    //过程分析                                                                                                                      //需要改
                    //任何时刻
                    if (HermesCalculator.reqQuShengAngle(float_array, 1, 3) < -35 && lineIndex % 40 == 0)
                    {
                        Console.WriteLine("系统检测到您的左腿抬起来了\n请注意是左脚支撑，抬右腿！");                                                                                     //需要改
                        m_tipFlag = 1;                                                                                     //需要改
                        m_tipContent = "系统检测到您的左腿抬起来了\n请注意是左脚支撑，抬右腿！";
                    }
                    else if (moveInCount >= 0 && lineIndex % 50 == 0 && HermesCalculator.reqQuShengAngle(float_array, 1, 3) >= -35)
                    {
                        Console.WriteLine("第一阶段采集完成！" + moveInCount);                                                                                     //需要改
                        m_tipFlag = 1;                                                                                     //需要改
                        m_tipContent = "采集到" + (moveInCount+1) + "组数据\n您可以继续再做一次\n也可以进入下一个动作！";                                                                                     //需要改
                        m_successFlag = 1;
                    }
                    moveInFlag = 0;
                }

                //更新进度条-在期望区间时
                if(m_hermesStateStablization_List[m_currentState + 1].stableTime <= 100 * 20
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1 && m_hermesStateStablization_List[m_currentState + 1].stablizedVariable[0] < -40)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)(100 * 20);
                    if (m_jindutiao > 1)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                    //Console.WriteLine("第一阶段采集完成！" + m_jindutiao);
                }
                else
                {
                    m_jindutiao = 0;
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 100);                                                                                     //需要改
            }
            else if (m_currentState == 1)                                                                                //需要改
            {

            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                
                if(m_successFlag != 1)
                {
                    m_successFlag = -1;
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "数据采集失败，\n请点击重做动作\n重做测试";
                }
                if(m_successFlag == 1 && lineIndex % 100 == 0)
                {
                    Console.WriteLine("测试时间结束！" + moveInCount);                                                                                     //需要改
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "测试时间结束！\n请点击下一个动作\n继续";
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改---
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();

            if(moveInCount == -1)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //左
            //求时间
            List<double> timeList = new List<double>();
            for (int i = -1; i <= moveInCount; i++)
            {
                if (i == -1)
                {
                    continue;
                }
                if (i >= 9)
                {
                    continue;
                }
                double time1 = processAngleListList[0 + 1, i][0];
                double time2 = processAngleListList[0 + 1, i][processAngleListList[0 + 1, i].Count - 1];
                timeList.Add(time2 - time1);
                Console.WriteLine("开始+结束： " + time1 + ' ' + time2);
            }

            HermesCalculator.printListDouble(timeList, "时间跨度");

            int index = 0;
            double timeMax = -999;
            for (int i = 0; i < timeList.Count; i++)
            {
                if(timeList[i] > timeMax)
                {
                    timeMax = timeList[i];
                    index = i;
                }
            }
            ret.Add("5007", (float)timeMax/100F + 1.0F);

            //左右时间不同
            if (HermesNewTest.m_tezhengDic_all.ContainsKey("YouCeDanJiaoZhiCheng") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["YouCeDanJiaoZhiCheng"].ContainsKey("5008") == true)
                {
                    float zuoce = ret["5007"];
                    float youce = HermesNewTest.m_tezhengDic_all["YouCeDanJiaoZhiCheng"]["5008"];
                    //左右时间不同（左侧-右侧）
                    ret.Add("5003", zuoce - youce);
                    if (HermesNewTest.m_tezhengDic_all["YouCeDanJiaoZhiCheng"].ContainsKey("5004") == true)
                    {
                        //左右时间不同（右侧 - 左侧）
                        HermesNewTest.m_tezhengDic_all["YouCeDanJiaoZhiCheng"]["5004"] = youce - zuoce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["YouCeDanJiaoZhiCheng"].Add("5004", youce - zuoce);
                    }
                }
            }

            //求脚的抖动最大值
            double[] meanValue1 = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 5, index], 0, processAngleListList[0 + 5, index].Count - 1);
            double[] meanValue2 = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 6, index], 0, processAngleListList[0 + 6, index].Count - 1);
            double[] meanValue3 = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 7, index], 0, processAngleListList[0 + 7, index].Count - 1);

            double maxMean = 0;
            if (Math.Abs(meanValue1[3]) > maxMean) maxMean = Math.Abs(meanValue1[3]);
            if (Math.Abs(meanValue2[3]) > maxMean) maxMean = Math.Abs(meanValue2[3]);
            if (Math.Abs(meanValue3[3]) > maxMean) maxMean = Math.Abs(meanValue3[3]);

            ret.Add("5005", (float)maxMean);

            Console.WriteLine("抖动情况： " + meanValue1[3] + ' ' + meanValue2[3] + ' ' + meanValue3[3] + ' ' + maxMean);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoCeDanJiaoZhiCheng") == true)
            {
                HermesNewTest.m_tezhengDic_all["ZuoCeDanJiaoZhiCheng"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ZuoCeDanJiaoZhiCheng", ret);
            }

            return ret;
        }


    }     //状态检测器-左侧单脚支撑

    public class HermesStateDetctorForYouCeDanJiaoZhiCheng : HermesStateDetctor     //状态检测器-右侧单脚支撑
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改
        public float[][] stageEndStateList = new float[stageNum + 8][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum + 8, 12];
        public int moveInCount;
        int moveInFlag;

        //初始化函数
        public HermesStateDetctorForYouCeDanJiaoZhiCheng()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            moveInCount = -1;
            moveInFlag = 0;
            //准备阶段稳定器                                                                                     //需要改
            float[] preVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedVariable_ = new float[] { 0, 0, 0, 0, 0, 0 };
            float[] expectedUp_ = new float[] { 15, 15, 20, 20, 20, 20 };
            float[] expectedDown_ = new float[] { 15, 15, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 7, 7, 7, 7, 7, 7 };
            float[] stableDown_ = new float[] { 7, 7, 7, 7, 7, 7 };
            int numOfVariable_ = 6;                                                                        //需要改
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改
            preVariable_ = new float[] { 250, 250 };
            expectedVariable_ = new float[] { 250, 250 };
            expectedUp_ = new float[] { 10, 10 };
            expectedDown_ = new float[] { 10, 10 };
            stableUp_ = new float[] { 30, 40 };
            stableDown_ = new float[] { 35, 20 };
            numOfVariable_ = 2;                                                                         //需要改
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum + 8; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 12; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改
                float[] variable_ = new float[] { 0, 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 0, 1);
                variable_[1] = HermesCalculator.reqQuShengAngle(float_array, 0, 2);
                variable_[2] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);
                variable_[3] = HermesCalculator.reqQuShengAngle(float_array, 2, 4);
                variable_[4] = HermesCalculator.reqQuShengAngle(float_array, 3, 5);
                variable_[5] = HermesCalculator.reqQuShengAngle(float_array, 4, 6);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    if (lineIndex <= 0 || lineIndex >= 15 * 60 * 60 * 100)
                    {
                        Console.WriteLine("准备阶段采集失败！");                                                                                     //需要改---
                        m_tipFlag = 1;                                                                                     //需要改---
                        m_tipContent = "准备阶段采集失败！";                                                                                     //需要改---
                        m_prepFlag = -1;                                                                                     //需要改---
                        m_jindutiao = 0;                                                                                     //需要改---
                        return;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改
                    m_prepFlag = 1;                                                                                     //需要改
                    m_jindutiao = 0;                                                                                     //需要改
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改---
                float[] variable_ = new float[] { 0, 0 };                                                                                     //需要改
                variable_[0] = HermesCalculator.reqQuShengAngle(float_array, 1, 3);                                   //需要改
                variable_[1] = HermesCalculator.reqQuShengAngleToGround(float_array, 0, 1);                                       //需要改
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值10次，超过10次算超时
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime && m_hermesStateStablization_List[m_currentState + 1].stableTime <= 100 * 20
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1 && m_hermesStateStablization_List[m_currentState + 1].stablizedVariable[0] < -40)
                {
                    //保存数据
                    if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime)
                    {
                        if (moveInFlag == 0)
                        {
                            moveInCount++;
                            moveInFlag = 1;
                        }
                    }
                    if (moveInCount >= 0 && moveInCount < 9)
                    {
                        //记录时间数据
                        processAngleListList[m_currentState + 1, moveInCount].Add(lineIndex);
                        //腰部前后倾
                        float yaobu_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 0, 0);
                        processAngleListList[m_currentState + 2, moveInCount].Add(yaobu_x);
                        //腰部旋转
                        float yaobu_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 0, 0);
                        processAngleListList[m_currentState + 3, moveInCount].Add(yaobu_z);
                        //左右摆动，向左-，向右+
                        float yaobu_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 0, 0);
                        processAngleListList[m_currentState + 4, moveInCount].Add(yaobu_y);
                        //右脚部前后倾
                        float jiao_x = HermesCalculator.reqYaobuQuShengAngleToGround(float_array, 6, 6);
                        processAngleListList[m_currentState + 5, moveInCount].Add(jiao_x);
                        //右脚部旋转
                        float jiao_z = HermesCalculator.reqNeixuanWaiXuanAngle3(float_array, 6, 6);
                        processAngleListList[m_currentState + 6, moveInCount].Add(jiao_z);
                        //右脚部左右摆动，向左-，向右+
                        float jiao_y = HermesCalculator.reqWaizhanNeishouAngleToGround3(float_array, 6, 6);
                        processAngleListList[m_currentState + 7, moveInCount].Add(jiao_y);
                    }
                    else if (moveInCount >= 9)
                    {
                        //跳出，进入下一阶段
                        m_currentState = 1;
                        Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改
                        m_tipFlag = 1;                                                                                     //需要改
                        m_tipContent = "动作采集完成\n您可以进入下一个动作！";                                                                                     //需要改
                        m_successFlag = 1;
                        return;
                    }
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 0)    //需要改
                {
                    //过程分析                                                                                                                      //需要改
                    //任何时刻
                    if (HermesCalculator.reqQuShengAngle(float_array, 2, 4) < -35 && lineIndex % 40 == 0)
                    {
                        Console.WriteLine("系统检测到您的右腿抬起来了\n请注意是右脚支撑，抬左腿！");                                                                                     //需要改
                        m_tipFlag = 1;                                                                                     //需要改
                        m_tipContent = "系统检测到您的右腿抬起来了\n请注意是右脚支撑，抬左腿！";
                    }
                    else if (moveInCount >= 0 && lineIndex % 50 == 0 && HermesCalculator.reqQuShengAngle(float_array, 2, 4) >= -35)
                    {
                        Console.WriteLine("第一阶段采集完成！" + moveInCount);                                                                                     //需要改
                        m_tipFlag = 1;                                                                                     //需要改
                        m_tipContent = "采集到" + (moveInCount + 1) + "组数据\n您可以继续再做一次\n也可以进入下一个动作！";                                                                                        //需要改
                        m_successFlag = 1;
                    }
                    moveInFlag = 0;
                }

                //更新进度条-在期望区间时

                if (m_hermesStateStablization_List[m_currentState + 1].stableTime <= 100 * 20
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1 && m_hermesStateStablization_List[m_currentState + 1].stablizedVariable[0] < -40)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)(100 * 20);
                    if (m_jindutiao > 1)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
                else
                {
                    m_jindutiao = 0;
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 100);                                                                                     //需要改
            }
            else if (m_currentState == 1)                                                                                //需要改
            {

            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "数据采集失败，\n请点击重做动作\n重做测试";
                }
                if (m_successFlag == 1 && lineIndex % 100 == 0)
                {
                    Console.WriteLine("测试时间结束！" + moveInCount);                                                                                     //需要改
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "测试时间结束！\n请点击下一个动作\n继续";
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改---
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();

            if (moveInCount == -1)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //左
            //求时间
            List<double> timeList = new List<double>();
            for (int i = -1; i <= moveInCount; i++)
            {
                if(i == -1)
                {
                    continue;
                }
                if (i >= 9)
                {
                    continue;
                }
                double time1 = processAngleListList[0 + 1, i][0];
                double time2 = processAngleListList[0 + 1, i][processAngleListList[0 + 1, i].Count - 1];
                timeList.Add(time2 - time1);
                Console.WriteLine("开始+结束： " + time1 + ' ' + time2);
            }

            HermesCalculator.printListDouble(timeList, "时间跨度");

            int index = 0;
            double timeMax = -999;
            for (int i = 0; i < timeList.Count; i++)
            {
                if (timeList[i] > timeMax)
                {
                    timeMax = timeList[i];
                    index = i;
                }
            }
            ret.Add("5008", (float)timeMax/100F + 1.0F);

            //左右侧时间不同
            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoCeDanJiaoZhiCheng") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["ZuoCeDanJiaoZhiCheng"].ContainsKey("5007") == true)
                {
                    float zuoce = HermesNewTest.m_tezhengDic_all["ZuoCeDanJiaoZhiCheng"]["5007"];
                    float youce = ret["5008"];
                    //两侧下蹲幅度不同（左侧-右侧）
                    ret.Add("5004", youce - zuoce);
                    if (HermesNewTest.m_tezhengDic_all["ZuoCeDanJiaoZhiCheng"].ContainsKey("5003") == true)
                    {
                        //两侧下蹲幅度不同（右侧 - 左侧）
                        HermesNewTest.m_tezhengDic_all["ZuoCeDanJiaoZhiCheng"]["5003"] = zuoce - youce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["ZuoCeDanJiaoZhiCheng"].Add("5003", zuoce - youce);
                    }
                }
            }

            //求脚的抖动最大值
            double[] meanValue1 = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 5, index], 0, processAngleListList[0 + 5, index].Count - 1);
            double[] meanValue2 = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 6, index], 0, processAngleListList[0 + 6, index].Count - 1);
            double[] meanValue3 = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 7, index], 0, processAngleListList[0 + 7, index].Count - 1);

            double maxMean = 0;
            if (Math.Abs(meanValue1[3]) > maxMean) maxMean = Math.Abs(meanValue1[3]);
            if (Math.Abs(meanValue2[3]) > maxMean) maxMean = Math.Abs(meanValue2[3]);
            if (Math.Abs(meanValue3[3]) > maxMean) maxMean = Math.Abs(meanValue3[3]);

            ret.Add("5006", (float)maxMean);

            Console.WriteLine("抖动情况： " + meanValue1[3] + ' ' + meanValue2[3] + ' ' + meanValue3[3] + ' ' + maxMean);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("YouCeDanJiaoZhiCheng") == true)
            {
                HermesNewTest.m_tezhengDic_all["YouCeDanJiaoZhiCheng"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("YouCeDanJiaoZhiCheng", ret);
            }

            return ret;
        }


    }     //状态检测器-右侧单脚支撑

    public class HermesStateDetctorForFuWoWeiZuoCeQuXiHouTaiTui : HermesStateDetctor     //状态检测器-后抬腿左
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 3;                                                                                      //需要改
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForFuWoWeiZuoCeQuXiHouTaiTui()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改
            float[] preVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 20, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改
            preVariable_ = new float[] { -80 };
            expectedVariable_ = new float[] { -80 };
            expectedUp_ = new float[] { 20 };
            expectedDown_ = new float[] { 60 };
            stableUp_ = new float[] { 5 };
            stableDown_ = new float[] { 5 };
            numOfVariable_ = 1;                                                                         //需要改
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器2                                                                                   //需要改
            preVariable_ = new float[] { 15 };
            expectedVariable_ = new float[] { 15 };
            expectedUp_ = new float[] { 40 };
            expectedDown_ = new float[] { 10 };
            stableUp_ = new float[] { 4 };
            stableDown_ = new float[] { 4 };
            numOfVariable_ = 1;                                                                         //需要改
            m_hermesStateStablization_List[2] = new HermesStateStablization();                         //需要改
            m_hermesStateStablization_List[2].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);      //需要改
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改
                    m_prepFlag = 1;                                                                                     //需要改
                    m_jindutiao = 0;                                                                                     //需要改
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改
                float[] variable_ = new float[] { 0 };                                                                                     //需要改
                variable_[0] = HermesCalculator.reqPaziQuShengAngle(float_array, 1, 3);    //需要改
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改
                    //m_successFlag = 1;                                                                                      //需要改
                    return;
                }

                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //状态2触发条件函数
        public void state2StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 1)
            {
                //状态1的通过稳定器
                float[] variable_ = new float[] { 0 };
                variable_[0] = HermesCalculator.reqPaziTuibuQuShengAngleToGround(float_array, 0, 1) - HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[0], 0, 1);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "2是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过100*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 2;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第二状态采集完成！");
                    m_tipFlag = 1;
                    m_tipContent = "第二阶段采集完成！";
                    m_successFlag = 1;
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 50);                                                                                     //需要改
            }
            else if (m_currentState == 1)                                                                                //需要改
            {
                state2StartGate(float_array, lineIndex, 200);                                                                                     //需要改
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            if(m_currentState < 2)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //左
            //左侧伸髋不足
            float angle = HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[2], 0, 1) - HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[0], 0, 1);
            ret.Add("2003", angle);
            Console.WriteLine("左侧伸髋不足： " + (float)angle);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("FuWoWeiYouCeQuXiHouTaiTui") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXiHouTaiTui"].ContainsKey("2004") == true)
                {
                    float zuoce = ret["2003"];
                    float youce = HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXiHouTaiTui"]["2004"];
                    //两侧伸髋不同（左侧-右侧）
                    ret.Add("2005", zuoce - youce);
                    if (HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXiHouTaiTui"].ContainsKey("2006") == true)
                    {
                        //两侧伸髋不同（右侧-左侧）
                        HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXiHouTaiTui"]["2006"] = youce - zuoce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXiHouTaiTui"].Add("2006", youce - zuoce);
                    }
                }
            }

            //骨盆逆时针旋转过度  ?
            angle = HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[2], 0, 0) - HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[0], 0, 0);
            ret.Add("1004", angle);
            Console.WriteLine("骨盆逆时针旋转过度： " + (float)angle);

            //骨盆前倾
            angle = HermesCalculator.reqPaziYaobuQuShengAngleToGround(stageEndStateList[2], 0, 0) - HermesCalculator.reqPaziYaobuQuShengAngleToGround(stageEndStateList[0], 0, 0);
            ret.Add("1005", angle);
            Console.WriteLine("骨盆前倾过度： " + (float)angle);

            //左髋外展过度
            angle = HermesCalculator.reqPaziWaizhan(stageEndStateList[2], 1, 2) - HermesCalculator.reqPaziWaizhan(stageEndStateList[0], 1, 2);
            ret.Add("2001", angle);
            Console.WriteLine("左髋外展过度： " + (float)angle);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("FuWoWeiZuoCeQuXiHouTaiTui") == true)
            {
                HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXiHouTaiTui"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("FuWoWeiZuoCeQuXiHouTaiTui", ret);
            }

            return ret;
        }


    }     //状态检测器-后抬腿左

    public class HermesStateDetctorForFuWoWeiYouCeQuXiHouTaiTui : HermesStateDetctor     //状态检测器-后抬腿右
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 3;                                                                                      //需要改-
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForFuWoWeiYouCeQuXiHouTaiTui()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改-
            float[] preVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 20, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改-
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改-
            preVariable_ = new float[] { -80 };
            expectedVariable_ = new float[] { -80 };
            expectedUp_ = new float[] { 20 };
            expectedDown_ = new float[] { 60 };
            stableUp_ = new float[] { 5 };
            stableDown_ = new float[] { 5 };
            numOfVariable_ = 1;                                                                         //需要改-
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器2                                                                                   //需要改-
            preVariable_ = new float[] { 15 };
            expectedVariable_ = new float[] { 15 };
            expectedUp_ = new float[] { 40 };
            expectedDown_ = new float[] { 10 };
            stableUp_ = new float[] { 4 };
            stableDown_ = new float[] { 4 };
            numOfVariable_ = 1;                                                                         //需要改-
            m_hermesStateStablization_List[2] = new HermesStateStablization();                         //需要改-
            m_hermesStateStablization_List[2].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);      //需要改-
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改-
                    m_prepFlag = 1;                                                                                     //需要改-
                    m_jindutiao = 0;                                                                                     //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改
                float[] variable_ = new float[] { 0 };                                                                                     //需要改
                variable_[0] = HermesCalculator.reqPaziQuShengAngle(float_array, 2, 4);    //需要改
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改
                    m_tipFlag = 1;                                                                                     //需要改
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改
                    //m_successFlag = 1;                                                                                      //需要改
                    return;
                }

                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //状态2触发条件函数
        public void state2StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 1)
            {
                //状态1的通过稳定器
                float[] variable_ = new float[] { 0 };
                variable_[0] = HermesCalculator.reqPaziTuibuQuShengAngleToGround(float_array, 0, 2) - HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[0], 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "2是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过100*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 2;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第二状态采集完成！");
                    m_tipFlag = 1;
                    m_tipContent = "第二阶段采集完成！";
                    m_successFlag = 1;
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 50);                                                                                     //需要改-
            }
            else if (m_currentState == 1)                                                                                //需要改-
            {
                state2StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            if (m_currentState < 2)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //右
            //右侧伸髋不足
            float angle = HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[2], 0, 2) - HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[0], 0, 2);
            ret.Add("2004", angle);
            Console.WriteLine("右侧伸髋不足： " + (float)angle);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("FuWoWeiZuoCeQuXiHouTaiTui") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXiHouTaiTui"].ContainsKey("2003") == true)
                {
                    float zuoce = HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXiHouTaiTui"]["2003"];
                    float youce = ret["2004"];
                    //两侧伸髋不同（右侧-左侧）
                    ret.Add("2006", youce - zuoce);
                    if (HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXiHouTaiTui"].ContainsKey("2005") == true)
                    {
                        //两侧伸髋不同（左侧-右侧）
                        HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXiHouTaiTui"]["2005"] = zuoce - youce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXiHouTaiTui"].Add("2005", zuoce - youce);
                    }
                }
            }

            //骨盆顺时针旋转过度  
            angle = HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[2], 0, 0) - HermesCalculator.reqPaziYaobuZXuanzhuan(stageEndStateList[0], 0, 0);
            ret.Add("1003", angle);
            Console.WriteLine("骨盆顺时针旋转过度： " + (float)angle);

            //骨盆前倾
            angle = HermesCalculator.reqPaziYaobuQuShengAngleToGround(stageEndStateList[2], 0, 0) - HermesCalculator.reqPaziYaobuQuShengAngleToGround(stageEndStateList[0], 0, 0);
            ret.Add("1005", angle);
            Console.WriteLine("骨盆前倾过度： " + (float)angle);

            //右髋外展过度
            angle = HermesCalculator.reqPaziWaizhan(stageEndStateList[2], 1, 2) - HermesCalculator.reqPaziWaizhan(stageEndStateList[0], 1, 2);
            ret.Add("2002", angle);
            Console.WriteLine("右髋外展过度： " + (float)angle);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("FuWoWeiYouCeQuXiHouTaiTui") == true)
            {
                HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXiHouTaiTui"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("FuWoWeiYouCeQuXiHouTaiTui", ret);
            }

            return ret;
        }


    }     //状态检测器-后抬腿右

    public class HermesStateDetctorForFuWoWeiZuoCeQuXi : HermesStateDetctor     //状态检测器-俯卧屈膝左
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改-
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForFuWoWeiZuoCeQuXi()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改-
            float[] preVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 20, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改-
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改-
            preVariable_ = new float[] { -80 };
            expectedVariable_ = new float[] { -80 };
            expectedUp_ = new float[] { 20 };
            expectedDown_ = new float[] { 60 };
            stableUp_ = new float[] { 5 };
            stableDown_ = new float[] { 5 };
            numOfVariable_ = 1;                                                                         //需要改-
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改-
                    m_prepFlag = 1;                                                                                     //需要改-
                    m_jindutiao = 0;                                                                                     //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0 };                                                                                     //需要改-
                variable_[0] = HermesCalculator.reqPaziQuShengAngle(float_array, 1, 3);    //需要改-
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改-
                    m_successFlag = 1;                                                                                      //需要改-
                    return;
                }

                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }
            else if (m_currentState == 1)                                                                                //需要改-
            {
                
            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            if (m_currentState < 1)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //左
            //左侧屈膝不足
            float angle = HermesCalculator.reqPaziQuShengAngle(stageEndStateList[1], 1, 3);
            ret.Add("3007", angle);
            Console.WriteLine("左侧屈膝不足： " + (float)angle);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("FuWoWeiYouCeQuXi") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXi"].ContainsKey("3008") == true)
                {
                    float zuoce = ret["3007"];
                    float youce = HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXi"]["3008"];
                    //两侧屈膝不同（左侧-右侧）
                    ret.Add("3009", zuoce - youce);
                    if (HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXi"].ContainsKey("3010") == true)
                    {
                        //两侧屈膝不同（右侧-左侧）
                        HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXi"]["3010"] = youce - zuoce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXi"].Add("3010", youce - zuoce);
                    }
                }
            }

            //骨盆前倾
            angle = HermesCalculator.reqPaziYaobuQuShengAngleToGround(stageEndStateList[1], 0, 0) - HermesCalculator.reqPaziYaobuQuShengAngleToGround(stageEndStateList[0], 0, 0);
            ret.Add("1005", angle);
            Console.WriteLine("骨盆前倾过度： " + (float)angle);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("FuWoWeiZuoCeQuXi") == true)
            {
                HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXi"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("FuWoWeiZuoCeQuXi", ret);
            }

            return ret;
        }


    }     //状态检测器-俯卧屈膝左

    public class HermesStateDetctorForFuWoWeiYouCeQuXi : HermesStateDetctor     //状态检测器-俯卧屈膝右
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改-
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForFuWoWeiYouCeQuXi()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改-
            float[] preVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 20, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改-
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改-
            preVariable_ = new float[] { -80 };
            expectedVariable_ = new float[] { -80 };
            expectedUp_ = new float[] { 20 };
            expectedDown_ = new float[] { 60 };
            stableUp_ = new float[] { 5 };
            stableDown_ = new float[] { 5 };
            numOfVariable_ = 1;                                                                         //需要改-
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改-
                    m_prepFlag = 1;                                                                                     //需要改-
                    m_jindutiao = 0;                                                                                     //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0 };                                                                                     //需要改-
                variable_[0] = HermesCalculator.reqPaziQuShengAngle(float_array, 2, 4);    //需要改-
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改-
                    m_successFlag = 1;                                                                                      //需要改-
                    return;
                }

                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }
            else if (m_currentState == 1)                                                                                //需要改-
            {

            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            if (m_currentState < 1)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //右
            //右侧屈膝不足
            float angle = HermesCalculator.reqPaziQuShengAngle(stageEndStateList[1], 2, 4);
            ret.Add("3008", angle);
            Console.WriteLine("左侧屈膝不足： " + (float)angle);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("FuWoWeiZuoCeQuXi") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXi"].ContainsKey("3007") == true)
                {
                    float zuoce = HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXi"]["3007"];
                    float youce = ret["3008"];
                    //两侧屈膝不足（右侧-左侧）
                    ret.Add("3010", youce - zuoce);
                    if (HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXi"].ContainsKey("3009") == true)
                    {
                        //两侧屈膝不足（左侧-右侧）
                        HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXi"]["3009"] = zuoce - youce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["FuWoWeiZuoCeQuXi"].Add("3009", zuoce - youce);
                    }
                }
            }

            //骨盆前倾
            angle = HermesCalculator.reqPaziYaobuQuShengAngleToGround(stageEndStateList[1], 0, 0) - HermesCalculator.reqPaziYaobuQuShengAngleToGround(stageEndStateList[0], 0, 0);
            ret.Add("1005", angle);
            Console.WriteLine("骨盆前倾过度： " + (float)angle);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("FuWoWeiYouCeQuXi") == true)
            {
                HermesNewTest.m_tezhengDic_all["FuWoWeiYouCeQuXi"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("FuWoWeiYouCeQuXi", ret);
            }

            return ret;
        }


    }     //状态检测器-俯卧屈膝右

    public class HermesStateDetctorForFuWoZuoCeXiaoTuiDaKai : HermesStateDetctor     //状态检测器-俯卧小腿打开
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改--
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForFuWoZuoCeXiaoTuiDaKai()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改--
            float[] preVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 20, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改--
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改--
            preVariable_ = new float[] { -80, 0, 0 };
            expectedVariable_ = new float[] { 100, -80, -80 };
            expectedUp_ = new float[] { 70, 20, 20 };
            expectedDown_ = new float[] { 40, 60, 60 };
            stableUp_ = new float[] { 5, 5, 5 };
            stableDown_ = new float[] { 5, 5, 5 };
            numOfVariable_ = 3;                                                                         //需要改--
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改--
                    m_tipFlag = 1;                                                                                     //需要改--
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改--
                    m_prepFlag = 1;                                                                                     //需要改--
                    m_jindutiao = 0;                                                                                     //需要改--
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改--
                float[] variable_ = new float[] { 0, 0, 0 };                                                                                     //需要改--
                variable_[0] = HermesCalculator.reqPaziXiaotuidakai(float_array, 1, 2);    //需要改--
                variable_[1] = HermesCalculator.reqPaziQuShengAngle(float_array, 1, 3);    //需要改--
                variable_[2] = HermesCalculator.reqPaziQuShengAngle(float_array, 2, 4);    //需要改--
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改--
                    m_tipFlag = 1;                                                                                     //需要改--
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改--
                    m_successFlag = 1;                                                                                      //需要改--
                    return;
                }

                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改--
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 200);                                                                                     //需要改--
            }
            else if (m_currentState == 1)                                                                                //需要改--
            {

            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            if (m_currentState < 1)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //左侧髋内旋过度
            float angle = HermesCalculator.reqPaziXiaotuidakaiDance(stageEndStateList[1], 0, 1);
            ret.Add("2022", angle);
            Console.WriteLine("左侧髋内旋过度： " + (float)angle);
            //右侧髋内旋过度
            angle = HermesCalculator.reqPaziXiaotuidakaiDance(stageEndStateList[1], 0, 2);
            ret.Add("2025", angle);
            Console.WriteLine("右侧髋内旋过度： " + (float)angle);
            //左侧髋内旋不足
            angle = HermesCalculator.reqPaziXiaotuidakaiDance(stageEndStateList[1], 0, 1);
            ret.Add("2020", angle);
            Console.WriteLine("左侧髋内旋不足： " + (float)angle);
            //右侧髋内旋不足
            angle = HermesCalculator.reqPaziXiaotuidakaiDance(stageEndStateList[1], 0, 2);
            ret.Add("2021", angle);
            Console.WriteLine("右侧髋内旋不足： " + (float)angle);

            //两侧髋内旋角度不同（左侧-右侧）
            ret.Add("2023", ret["2020"] + ret["2021"]);
            Console.WriteLine("两侧髋内旋角度不同（左侧-右侧）： " + (float)(ret["2020"] + ret["2021"]));

            //两侧髋内旋角度不同（右侧-左侧）
            ret.Add("2024", ret["2021"] + ret["2020"]);
            Console.WriteLine("两侧髋内旋角度不同（右侧-左侧）： " + (float)(ret["2021"] + ret["2020"]));

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("FuWoZuoCeXiaoTuiDaKai") == true)
            {
                HermesNewTest.m_tezhengDic_all["FuWoZuoCeXiaoTuiDaKai"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("FuWoZuoCeXiaoTuiDaKai", ret);
            }

            return ret;
        }


    }     //状态检测器-俯卧小腿打开

    public class HermesStateDetctorForZuoZiZuoCeSiZiCeShi : HermesStateDetctor     //状态检测器-坐姿四字测试左
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改--
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForZuoZiZuoCeSiZiCeShi()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改---
            float[] preVariable_ = new float[] { 50, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 50, 90, 90, 90, 90 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 50, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改---
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改---
            preVariable_ = new float[] { 0, 0 };
            expectedVariable_ = new float[] { 90, 0};
            expectedUp_ = new float[] { 40, 20 };
            expectedDown_ = new float[] { 20, 25 };
            stableUp_ = new float[] { 3, 3};
            stableDown_ = new float[] { 3, 3,};
            numOfVariable_ = 2;                                                                         //需要改---
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改---
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改---
                    m_tipFlag = 1;                                                                                     //需要改---
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改---
                    m_prepFlag = 1;                                                                                     //需要改---
                    m_jindutiao = 0;                                                                                     //需要改---
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改---
                float[] variable_ = new float[] { 0, 0, 0 };                                                                                     //需要改---
                variable_[0] = HermesCalculator.reqZuoziQuShengAngle(float_array, 1, 3);    //需要改---
                variable_[1] = HermesCalculator.reqZuoziQuShengAngle(float_array, 2, 4);    //需要改---
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改---
                    m_tipFlag = 1;                                                                                     //需要改---
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改---
                    m_successFlag = 1;                                                                                      //需要改---
                    return;
                }

                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改---
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 200);                                                                                     //需要改---
            }
            else if (m_currentState == 1)                                                                                //需要改---
            {

            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            if (m_currentState < 1)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //左侧大腿无法放下
            float angle1 = HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[1], 0, 1) - HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[0], 0, 1);
            float angle2 = HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[1], 0, 3) - HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[0], 0, 3);
            ret.Add("2009", angle1 + angle2);
            Console.WriteLine("左侧大腿无法放下： " + (float)angle1 + " " + (float)angle2);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoZiYouCeSiZiCeShi") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["ZuoZiYouCeSiZiCeShi"].ContainsKey("2010") == true)
                {
                    float zuoce = ret["2009"];
                    float youce = HermesNewTest.m_tezhengDic_all["ZuoZiYouCeSiZiCeShi"]["2010"];
                    //两侧大腿放下角度不同（左侧-右侧）2012
                    ret.Add("2012", zuoce - youce);
                    if (HermesNewTest.m_tezhengDic_all["ZuoZiYouCeSiZiCeShi"].ContainsKey("2013") == true)
                    {
                        //两侧大腿放下角度不同（右侧-左侧）2013
                        HermesNewTest.m_tezhengDic_all["ZuoZiYouCeSiZiCeShi"]["2013"] = youce - zuoce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["ZuoZiYouCeSiZiCeShi"].Add("2013", youce - zuoce);
                    }
                }
            }

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoZiZuoCeSiZiCeShi") == true)
            {
                HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeSiZiCeShi"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ZuoZiZuoCeSiZiCeShi", ret);
            }

            return ret;
        }


    }     //状态检测器-坐姿四字测试左

    public class HermesStateDetctorForZuoZiYouCeSiZiCeShi : HermesStateDetctor     //状态检测器-坐姿四字测试右
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改--
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForZuoZiYouCeSiZiCeShi()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改---
            float[] preVariable_ = new float[] { 50, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 50, 90, 90, 90, 90 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 50, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改---
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改---
            preVariable_ = new float[] { 0, 0 };
            expectedVariable_ = new float[] { -90, 0 };
            expectedUp_ = new float[] { 20, 20 };
            expectedDown_ = new float[] { 40, 25 };
            stableUp_ = new float[] { 3, 3 };
            stableDown_ = new float[] { 3, 3, };
            numOfVariable_ = 2;                                                                         //需要改---
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改---
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改---
                    m_tipFlag = 1;                                                                                     //需要改---
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改---
                    m_prepFlag = 1;                                                                                     //需要改---
                    m_jindutiao = 0;                                                                                     //需要改---
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改---
                float[] variable_ = new float[] { 0, 0, 0 };                                                                                     //需要改---
                variable_[0] = HermesCalculator.reqZuoziQuShengAngle(float_array, 2, 4);    //需要改---
                variable_[1] = HermesCalculator.reqZuoziQuShengAngle(float_array, 1, 3);    //需要改---
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改---
                    m_tipFlag = 1;                                                                                     //需要改---
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改---
                    m_successFlag = 1;                                                                                      //需要改---
                    return;
                }

                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改---
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 200);                                                                                     //需要改---
            }
            else if (m_currentState == 1)                                                                                //需要改---
            {

            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            if (m_currentState < 1)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //右侧大腿无法放下
            float angle1 = HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[1], 0, 2) - HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[0], 0, 2);
            float angle2 = HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[1], 0, 4) - HermesCalculator.reqPaziTuibuQuShengAngleToGround(stageEndStateList[0], 0, 4);
            ret.Add("2010", angle1 + angle2);
            Console.WriteLine("右侧大腿无法放下： " + (float)angle1 + " " + (float)angle2);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoZiZuoCeSiZiCeShi") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeSiZiCeShi"].ContainsKey("2009") == true)
                {
                    float zuoce = HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeSiZiCeShi"]["2009"];
                    float youce = ret["2010"];
                    //两侧大腿放下角度不同（右侧-左侧）2013
                    ret.Add("2013", -zuoce + youce);
                    if (HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeSiZiCeShi"].ContainsKey("2012") == true)
                    {
                        //两侧大腿放下角度不同（左侧-右侧）2012
                        HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeSiZiCeShi"]["2012"] = -youce + zuoce;
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeSiZiCeShi"].Add("2012", -youce + zuoce);
                    }
                }
            }

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoZiYouCeSiZiCeShi") == true)
            {
                HermesNewTest.m_tezhengDic_all["ZuoZiYouCeSiZiCeShi"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ZuoZiYouCeSiZiCeShi", ret);
            }

            return ret;
        }


    }     //状态检测器-坐姿四字测试右

    public class HermesStateDetctorForZuoZiZuoCeZhiTuiNeiShou : HermesStateDetctor     //状态检测器-坐姿左侧直腿内收
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改-
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForZuoZiZuoCeZhiTuiNeiShou()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改-
            float[] preVariable_ = new float[] { 50, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 50, 90, 90, 90, 90 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 50, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改-
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改-
            preVariable_ = new float[] { 0, 0, 0, 0};
            expectedVariable_ = new float[] { 10, 10, 0, 0 };
            expectedUp_ = new float[] { 30, 50, 5, 10};
            expectedDown_ = new float[] { 5, 5, 5, 10 };
            stableUp_ = new float[] { 3, 3, 2, 3 };
            stableDown_ = new float[] { 3, 3, 2, 3};
            numOfVariable_ = 4;                                                                         //需要改-
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改-
                    m_prepFlag = 1;                                                                                     //需要改-
                    m_jindutiao = 0;                                                                                     //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0 };                                                                                     //需要改-
                variable_[0] = HermesCalculator.reqZuoziNeishou(float_array, 0, 1) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 1);    //需要改-
                variable_[1] = HermesCalculator.reqZuoziNeishou(float_array, 0, 3) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 3);    //需要改-
                variable_[2] = HermesCalculator.reqZuoziNeishou(float_array, 0, 2) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 2);    //需要改-
                variable_[3] = HermesCalculator.reqZuoziNeishou(float_array, 0, 4) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 4);    //需要改-
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改-
                    m_successFlag = 1;                                                                                      //需要改-
                    return;
                }

                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }
            else if (m_currentState == 1)                                                                                //需要改-
            {

            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            if (m_currentState < 1)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //左侧内收不足2016
            float angle1 = HermesCalculator.reqZuoziNeishou(stageEndStateList[1], 0, 1) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 1);
            float angle2 = HermesCalculator.reqZuoziNeishou(stageEndStateList[1], 0, 3) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 3);
            ret.Add("2016", angle1 + angle2);
            Console.WriteLine("左侧内收不足2016： " + (float)angle1 + " " + (float)angle2);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoZiYouCeZhiTuiNeiShou") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["ZuoZiYouCeZhiTuiNeiShou"].ContainsKey("2017") == true)
                {
                    float zuoce = ret["2016"];
                    float youce = HermesNewTest.m_tezhengDic_all["ZuoZiYouCeZhiTuiNeiShou"]["2017"];
                    //两侧内收角度不同（左侧-右侧）2018
                    ret.Add("2018", Math.Abs(zuoce) - Math.Abs(youce));
                    if (HermesNewTest.m_tezhengDic_all["ZuoZiYouCeZhiTuiNeiShou"].ContainsKey("2019") == true)
                    {
                        //两侧内收角度不同（右侧-左侧）2019
                        HermesNewTest.m_tezhengDic_all["ZuoZiYouCeZhiTuiNeiShou"]["2019"] = Math.Abs(youce) - Math.Abs(zuoce);
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["ZuoZiYouCeZhiTuiNeiShou"].Add("2019", Math.Abs(youce) - Math.Abs(zuoce));
                    }
                }
            }

            //内收会发生小腿打完代偿，需要在后期进行识别并做出解释

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoZiZuoCeZhiTuiNeiShou") == true)
            {
                HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeZhiTuiNeiShou"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ZuoZiZuoCeZhiTuiNeiShou", ret);
            }

            return ret;
        }


    }     //状态检测器-坐姿左侧直腿内收

    public class HermesStateDetctorForZuoZiYouCeZhiTuiNeiShou : HermesStateDetctor     //状态检测器-坐姿右侧直腿内收
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改-
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForZuoZiYouCeZhiTuiNeiShou()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改-
            float[] preVariable_ = new float[] { 50, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 50, 90, 90, 90, 90 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 50, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改-
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改-
            preVariable_ = new float[] { 0, 0, 0, 0 };
            expectedVariable_ = new float[] { 0, 0, -10, -10 };
            expectedUp_ = new float[] { 5, 10, 5, 5 };
            expectedDown_ = new float[] { 5, 10, 30, 50 };
            stableUp_ = new float[] { 2, 3, 3, 3 };
            stableDown_ = new float[] { 2, 3, 3, 3 };
            numOfVariable_ = 4;                                                                         //需要改-
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改-
                    m_prepFlag = 1;                                                                                     //需要改-
                    m_jindutiao = 0;                                                                                     //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0 };                                                                                     //需要改-
                variable_[0] = HermesCalculator.reqZuoziNeishou(float_array, 0, 1) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 1);    //需要改-
                variable_[1] = HermesCalculator.reqZuoziNeishou(float_array, 0, 3) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 3);    //需要改-
                variable_[2] = HermesCalculator.reqZuoziNeishou(float_array, 0, 2) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 2);    //需要改-
                variable_[3] = HermesCalculator.reqZuoziNeishou(float_array, 0, 4) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 4);    //需要改-
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "动作采集完成，可以站起来了！";                                                                                     //需要改-
                    m_successFlag = 1;                                                                                      //需要改-
                    return;
                }

                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime * (1.0F / (stageNum - 1)) + (float)(m_currentState) / (float)(stageNum - 1) + 0.05F;
                    if (m_jindutiao > (float)(m_currentState + 1) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState + 1) / (float)(stageNum - 1);
                    }
                    else if (m_jindutiao < (float)(m_currentState) / (float)(stageNum - 1))
                    {
                        m_jindutiao = (float)(m_currentState) / (float)(stageNum - 1);
                    }
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 200);                                                                                     //需要改-
            }
            else if (m_currentState == 1)                                                                                //需要改-
            {

            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();
            if (m_currentState < 1)
            {
                Console.WriteLine("return ");
                return ret;
            }

            //右侧内收不足2017
            float angle1 = HermesCalculator.reqZuoziNeishou(stageEndStateList[1], 0, 2) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 2);
            float angle2 = HermesCalculator.reqZuoziNeishou(stageEndStateList[1], 0, 4) - HermesCalculator.reqZuoziNeishou(stageEndStateList[0], 0, 4);
            ret.Add("2017", angle1 + angle2);
            Console.WriteLine("右侧内收不足2017： " + (float)angle1 + " " + (float)angle2);

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoZiZuoCeZhiTuiNeiShou") == true)
            {
                if (HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeZhiTuiNeiShou"].ContainsKey("2016") == true)
                {
                    float zuoce = HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeZhiTuiNeiShou"]["2016"]; 
                    float youce = ret["2017"];
                    //两侧内收角度不同（右侧-左侧）2019
                    ret.Add("2019", -Math.Abs(zuoce) + Math.Abs(youce));
                    if (HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeZhiTuiNeiShou"].ContainsKey("2018") == true)
                    {
                        //两侧内收角度不同（左侧-右侧）2018
                        HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeZhiTuiNeiShou"]["2018"] = -Math.Abs(youce) + Math.Abs(zuoce);
                    }
                    else
                    {
                        HermesNewTest.m_tezhengDic_all["ZuoZiZuoCeZhiTuiNeiShou"].Add("2018", -Math.Abs(youce) + Math.Abs(zuoce));
                    }
                }
            }

            //内收会发生小腿打完代偿，需要在后期进行识别并做出解释

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("ZuoZiYouCeZhiTuiNeiShou") == true)
            {
                HermesNewTest.m_tezhengDic_all["ZuoZiYouCeZhiTuiNeiShou"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("ZuoZiYouCeZhiTuiNeiShou", ret);
            }

            return ret;
        }


    }     //状态检测器-坐姿右侧直腿内收

    public class HermesStateDetctorForCeMianChengZuoTuiTaiTui : HermesStateDetctor     //状态检测器-侧面撑左腿抬腿3次
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改-
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForCeMianChengZuoTuiTaiTui()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改-?
            float[] preVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 20, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改-
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改-
            preVariable_ = new float[] { 250 };
            expectedVariable_ = new float[] { 250 };
            expectedUp_ = new float[] { 10 };
            expectedDown_ = new float[] { 10 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;                                                                         //需要改-
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改-
                    m_prepFlag = 1;                                                                                     //需要改-
                    m_jindutiao = 0;                                                                                     //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0 };                                                                                     //需要改-
                variable_[0] = HermesCalculator.reqPaziWaizhan2(float_array, 0, 3) - HermesCalculator.reqPaziWaizhan(stageEndStateList[0], 0, 3);    //需要改-
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "动作采集完成！";                                                                                     //需要改-
                    //m_successFlag = 1;                                                                                      //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 0)    //需要改-
                {
                    //过程分析                                                                                                                      //需要改-
                    //任何时刻
                    //骨盆左右旋转
                    float angle = HermesCalculator.reqCechengWaizhan2(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 0].Add(angle);
                    //左大腿夹角
                    angle = HermesCalculator.reqCechengWaizhan2(float_array, 0, 1);
                    processAngleListList[m_currentState + 1, 1].Add(angle);
                    //右大腿夹角
                    angle = HermesCalculator.reqCechengWaizhan2(float_array, 0, 2);
                    processAngleListList[m_currentState + 1, 2].Add(angle);
                    //骨盆旋转
                    angle = HermesCalculator.reqCechengYaobuZXuanzhuanLeft(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 3].Add(angle);
                    //左大腿夹角差
                    angle = HermesCalculator.reqCechengWaizhan2(float_array, 0, 1) - HermesCalculator.reqCechengWaizhan2(stageEndStateList[0], 0, 1);
                    processAngleListList[m_currentState + 1, 4].Add(angle);
                    //右大腿夹角差
                    angle = HermesCalculator.reqCechengWaizhan2(float_array, 0, 2) - HermesCalculator.reqCechengWaizhan2(stageEndStateList[0], 0, 2);
                    processAngleListList[m_currentState + 1, 5].Add(angle);
                }

                if (lineIndex % 90 == 0)
                {
                    List<double> xiaotuijiajiao_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 4, 26);
                    List<int> xiaotuijiajiao_min = HermesCalculator.huaxianValueDown(xiaotuijiajiao_pinhua, -10, 26);
                    motionCount = xiaotuijiajiao_min.Count;

                    Console.WriteLine("第一阶段采集完成！数量：" + motionCount);

                    if (motionCount >= 3)
                    {
                        m_currentState = 1;
                        Console.WriteLine("第一阶段采集完成！数量");                                                                                     //需要改-
                        m_tipFlag = 1;                                                                                     //需要改-
                        m_tipContent = "动作采集完成！";                                                                                     //需要改-
                        m_successFlag = 1;
                        m_jindutiao = 1;
                        return;
                    }
                }

                //更新进度条-在期望区间时
                m_jindutiao = (float)motionCount / (float)3;
                if (m_jindutiao > 1)
                {
                    m_jindutiao = 1;
                }
                else if (m_jindutiao < 0)
                {
                    m_jindutiao = 0;
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 100);                                                                                     //需要改-
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 300);                                                                                     //需要改-
            }
            else if (m_currentState == 1)                                                                                //需要改-
            {

            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改-
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();

            //左
            //求左大腿的夹角最小值-左
            List<double> xiaotuijiajiao_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 4, 26);
            List<int> xiaotuijiajiao_min = HermesCalculator.huaxianValueDown(xiaotuijiajiao_pinhua, -10, 26);
            HermesCalculator.printList(xiaotuijiajiao_min, "左大腿的夹角最小值");

            if (xiaotuijiajiao_min.Count < 2)
            {
                return ret;
            }

            //求左大腿的夹角最大值 - 左
            List<int> xiaotuijiajiao_max = HermesCalculator.huaxianValueUp(xiaotuijiajiao_pinhua, -20, 26);
            HermesCalculator.printList(xiaotuijiajiao_max, "左大腿的夹角最大值");

            //骨盆掉落- 左
            //求左大腿的夹角最大值
            List<double> angleList = new List<double>();
            angleList.Add(HermesCalculator.reqCechengWaizhan2(stageEndStateList[0], 0, 2) - HermesCalculator.reqCechengWaizhan2(stageEndStateList[0], 0, 0));
            for (int i = 0; i < xiaotuijiajiao_max.Count; i++)
            {
                if(xiaotuijiajiao_max[i] <= xiaotuijiajiao_min[xiaotuijiajiao_min.Count -1] && xiaotuijiajiao_max[i] >= xiaotuijiajiao_min[0])
                {
                    //右腿 - 骨盆
                    angleList.Add(processAngleListList[1, 2][xiaotuijiajiao_max[i]] - processAngleListList[1, 0][xiaotuijiajiao_max[i]]);
                    Console.WriteLine("1： " + (float)processAngleListList[1, 2][xiaotuijiajiao_max[i]]);
                    Console.WriteLine("2： " + (float)processAngleListList[1, 0][xiaotuijiajiao_max[i]]);
                }  
            }
            HermesCalculator.printListDouble(angleList, "骨盆掉落 - 左");
            double[] xxxx = HermesCalculator.calMaxMinMeanVar(angleList, 0, angleList.Count - 1);
            Console.WriteLine("骨盆掉落- 左 - 最大值： " + (float)(xxxx[0] - angleList[0]));
            Console.WriteLine("骨盆掉落- 左 - 最小值： " + (float)(xxxx[1] - angleList[0]));
            float max = (float)(xxxx[0] - angleList[0]);
            float min = (float)(xxxx[1] - angleList[0]);
            if(Math.Abs(max) > Math.Abs(min))
            {
                //骨盆左侧掉落1007
                ret.Add("1007", max);
            }
            else
            {
                //骨盆左侧掉落1007
                ret.Add("1007", min);
            }

            //骨盆旋转 - 左
            double[] xxx = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 3], 0, processAngleListList[0 + 1, 3].Count -1);
            Console.WriteLine("骨盆旋转 - 左 - 最大值： " + (float)(xxx[0] - HermesCalculator.reqCechengYaobuZXuanzhuanLeft(stageEndStateList[0], 0, 0) )    );
            Console.WriteLine("骨盆旋转 - 左 - 最小值： " + (float)(xxx[1] - HermesCalculator.reqCechengYaobuZXuanzhuanLeft(stageEndStateList[0], 0, 0) )    );
            max = (float)(xxx[0] - HermesCalculator.reqCechengYaobuZXuanzhuanLeft(stageEndStateList[0], 0, 0));
            min = (float)(xxx[1] - HermesCalculator.reqCechengYaobuZXuanzhuanLeft(stageEndStateList[0], 0, 0));
            if (Math.Abs(max) > Math.Abs(min))
            {
                //骨盆左侧歪斜1009
                ret.Add("1009", max);
            }
            else
            {
                //骨盆左侧歪斜1009
                ret.Add("1009", min);
            }

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("CeMianChengZuoTuiTaiTui") == true)
            {
                HermesNewTest.m_tezhengDic_all["CeMianChengZuoTuiTaiTui"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("CeMianChengZuoTuiTaiTui", ret);
            }

            return ret;
        }


    }     //状态检测器-侧面撑左腿抬腿3次

    public class HermesStateDetctorForCeMianChengYouTuiTaiTui : HermesStateDetctor     //状态检测器-侧面撑右腿抬腿3次
    {
        //当前状态
        public int m_currentState;
        //动作完成情况
        public int m_currentStateExistTime;
        //阶段状态List
        const int stageNum = 2;                                                                                      //需要改-
        public float[][] stageEndStateList = new float[stageNum][];
        ////准备阶段状态
        //public float[] prepEndState = new float[4 * 7 + 1];
        ////动作阶段1结束状态
        //public float[] stage1EndState = new float[4 * 7 + 1];
        ////动作阶段2结束状态
        //public float[] stage2EndState = new float[4 * 7 + 1];
        public HermesStateStablization[] m_hermesStateStablization_List = new HermesStateStablization[stageNum];
        //public HermesStateStablization m_hermesStateStablization_stage1;
        //public HermesStateStablization m_hermesStateStablization_stage2;
        //public HermesStateStablization m_hermesStateStablization_prep;
        public List<double>[,] processAngleListList = new List<double>[stageNum, 10];

        int motionCount;

        //初始化函数
        public HermesStateDetctorForCeMianChengYouTuiTaiTui()
        {
            reset();
        }

        public override void reset()
        {
            m_currentState = -1;
            m_currentStateExistTime = 0;
            motionCount = 0;
            //准备阶段稳定器                                                                                     //需要改-?
            float[] preVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedVariable_ = new float[] { 90, 70, 70, 70, 70 };
            float[] expectedUp_ = new float[] { 30, 30, 30, 30, 30 };
            float[] expectedDown_ = new float[] { 20, 20, 20, 20, 20 };
            float[] stableUp_ = new float[] { 10, 15, 15, 15, 15 };
            float[] stableDown_ = new float[] { 10, 15, 15, 15, 15 };
            int numOfVariable_ = 5;                                                                        //需要改-
            m_hermesStateStablization_List[0] = new HermesStateStablization();
            m_hermesStateStablization_List[0].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //创建状态稳定器1                                                                                     //需要改-
            preVariable_ = new float[] { 250 };
            expectedVariable_ = new float[] { 250 };
            expectedUp_ = new float[] { 10 };
            expectedDown_ = new float[] { 10 };
            stableUp_ = new float[] { 3 };
            stableDown_ = new float[] { 3 };
            numOfVariable_ = 1;                                                                         //需要改-
            m_hermesStateStablization_List[1] = new HermesStateStablization();
            m_hermesStateStablization_List[1].reset(preVariable_, expectedVariable_, expectedUp_, expectedDown_, stableUp_, stableDown_, numOfVariable_);
            //状态List + 过程List
            for (int i = 0; i < stageNum; i++)
            {
                stageEndStateList[i] = new float[4 * 7 + 3 * 7 + 3 * 7 + 1];
                for (int j = 0; j < 10; j++)
                {
                    processAngleListList[i, j] = new List<double>();
                }
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
        }

        //准备阶段触发条件函数
        public void state0StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == -1)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0, 0, 0, 0, 0 };
                variable_[0] = HermesCalculator.reqMainAngleRelative(float_array[4 * 0 + 3], float_array[4 * 0 + 0], float_array[4 * 0 + 1], float_array[4 * 0 + 2], 2, 1, 0, 0, 0, 2);
                variable_[1] = HermesCalculator.reqMainAngleRelative(float_array[4 * 1 + 3], float_array[4 * 1 + 0], float_array[4 * 1 + 1], float_array[4 * 1 + 2], 2, 1, 0, 0, 0, 2);
                variable_[2] = HermesCalculator.reqMainAngleRelative(float_array[4 * 2 + 3], float_array[4 * 2 + 0], float_array[4 * 2 + 1], float_array[4 * 2 + 2], 2, 1, 0, 0, 0, 2);
                variable_[3] = HermesCalculator.reqMainAngleRelative(float_array[4 * 3 + 3], float_array[4 * 3 + 0], float_array[4 * 3 + 1], float_array[4 * 3 + 2], 2, 1, 0, 0, 0, 2);
                variable_[4] = HermesCalculator.reqMainAngleRelative(float_array[4 * 4 + 3], float_array[4 * 4 + 0], float_array[4 * 4 + 1], float_array[4 * 4 + 2], 2, 1, 0, 0, 0, 2);
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);
                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 0;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }

                    Console.WriteLine("准备阶段采集完成！动作开始！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "准备阶段采集完成！动作开始！";                                                                                     //需要改-
                    m_prepFlag = 1;                                                                                     //需要改-
                    m_jindutiao = 0;                                                                                     //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].stableTime < stableWaitTime)
                {
                    //过程分析
                }
                //更新进度条-在期望区间时
                if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1)
                {
                    m_jindutiao = (float)m_hermesStateStablization_List[m_currentState + 1].stableTime / (float)stableWaitTime;
                    if (m_jindutiao > 1.0)
                    {
                        m_jindutiao = 1;
                    }
                    else if (m_jindutiao < 0)
                    {
                        m_jindutiao = 0;
                    }
                }
            }
        }

        //状态1触发条件函数
        public void state1StartGate(float[] float_array, int lineIndex, int stableWaitTime)
        {

            //只有满足条件的动作才能开始计数
            if (m_currentState == 0)
            {
                //状态1的通过稳定器                                                                                     //需要改-
                float[] variable_ = new float[] { 0 };                                                                                     //需要改-
                variable_[0] = HermesCalculator.reqPaziWaizhan2(float_array, 0, 3) - HermesCalculator.reqPaziWaizhan(stageEndStateList[0], 0, 3);    //需要改-
                m_hermesStateStablization_List[m_currentState + 1].stableState(variable_, stableWaitTime);

                //string stableStateString = "";
                //stableStateString += "1是否是期望区间XXXXXX：" + m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea + "序号：" + m_currentState;
                //Console.WriteLine(stableStateString);

                //如果稳定时间超过50*10ms，保留数值并进入下一个环节
                if (m_hermesStateStablization_List[m_currentState + 1].stableTime >= stableWaitTime
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 1
                    && m_hermesStateStablization_List[m_currentState + 1].m_isAllInStableArea == 1)
                {
                    m_currentState = 1;
                    //保留快照，并进入下一环节
                    for (int i = 0; i < 7; i++)
                    {
                        stageEndStateList[m_currentState][4 * i + 3] = float_array[4 * i + 3];
                        stageEndStateList[m_currentState][4 * i + 0] = float_array[4 * i + 0];
                        stageEndStateList[m_currentState][4 * i + 1] = float_array[4 * i + 1];
                        stageEndStateList[m_currentState][4 * i + 2] = float_array[4 * i + 2];
                        stageEndStateList[m_currentState][4 * 7 + 3 * 7 + 3 * 7] = lineIndex;
                    }
                    Console.WriteLine("第一阶段采集完成！");                                                                                     //需要改-
                    m_tipFlag = 1;                                                                                     //需要改-
                    m_tipContent = "动作采集完成！";                                                                                     //需要改-
                    //m_successFlag = 1;                                                                                      //需要改-
                    return;
                }
                else if (m_hermesStateStablization_List[m_currentState + 1].m_isAllInExpectedArea == 0)    //需要改-
                {
                    //过程分析                                                                                                                      //需要改-
                    //任何时刻
                    //骨盆左右旋转
                    float angle = HermesCalculator.reqCechengWaizhan2(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 0].Add(angle);
                    //左大腿夹角
                    angle = HermesCalculator.reqCechengWaizhan2(float_array, 0, 1);
                    processAngleListList[m_currentState + 1, 1].Add(angle);
                    //右大腿夹角
                    angle = HermesCalculator.reqCechengWaizhan2(float_array, 0, 2);
                    processAngleListList[m_currentState + 1, 2].Add(angle);
                    //骨盆旋转
                    angle = HermesCalculator.reqCechengYaobuZXuanzhuanRight(float_array, 0, 0);
                    processAngleListList[m_currentState + 1, 3].Add(angle);
                    //左大腿夹角差
                    angle = HermesCalculator.reqCechengWaizhan2(float_array, 0, 1) - HermesCalculator.reqCechengWaizhan2(stageEndStateList[0], 0, 1);
                    processAngleListList[m_currentState + 1, 4].Add(angle);
                    //右大腿夹角差
                    angle = HermesCalculator.reqCechengWaizhan2(float_array, 0, 2) - HermesCalculator.reqCechengWaizhan2(stageEndStateList[0], 0, 2);
                    processAngleListList[m_currentState + 1, 5].Add(angle);
                }

                if (lineIndex % 90 == 0)
                {
                    List<double> xiaotuijiajiao_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 5, 26);
                    List<int> xiaotuijiajiao_min = HermesCalculator.huaxianValueUp(xiaotuijiajiao_pinhua, 10, 26);
                    motionCount = xiaotuijiajiao_min.Count;

                    Console.WriteLine("第一阶段采集完成！数量：" + motionCount);

                    if (motionCount >= 3)
                    {
                        m_currentState = 1;
                        Console.WriteLine("第一阶段采集完成！数量");                                                                                     //需要改-
                        m_tipFlag = 1;                                                                                     //需要改-
                        m_tipContent = "动作采集完成！";                                                                                     //需要改-
                        m_successFlag = 1;
                        m_jindutiao = 1;
                        return;
                    }
                }

                //更新进度条-在期望区间时
                m_jindutiao = (float)motionCount / (float)3;
                if (m_jindutiao > 1)
                {
                    m_jindutiao = 1;
                }
                else if (m_jindutiao < 0)
                {
                    m_jindutiao = 0;
                }
            }
        }

        //准备阶段状态处理器
        public override void calcPrep(float[] float_array, int lineIndex)
        {
            //检查当前状态，尝试进入下一状态
            if (m_currentState == -1)
            {
                state0StartGate(float_array, lineIndex, 100);                                                                                     //需要改-
            }
        }

        //状态处理器
        public override void calc(float[] float_array, int lineIndex, int delayTime_10ms)
        {
            //检查当前状态，尝试进入下一状态
            //加入超时功能
            int old_lineIndex = (int)stageEndStateList[0][4 * 7 + 3 * 7 + 3 * 7];
            if (m_currentState == 0 && lineIndex - old_lineIndex <= delayTime_10ms)
            {
                state1StartGate(float_array, lineIndex, 300);                                                                                     //需要改-
            }
            else if (m_currentState == 1)                                                                                //需要改-
            {

            }

            if (lineIndex - old_lineIndex > delayTime_10ms)
            {
                Console.WriteLine("动作超时！");
                if (m_successFlag != 1)
                {
                    m_successFlag = -1;
                }
            }
        }

        //获得特征
        public override Dictionary<string, float> getTezheng()                                                                                    //需要改-
        {
            Dictionary<string, float> ret = new Dictionary<string, float>();

            //左
            //求右大腿的夹角最大值-左
            List<double> xiaotuijiajiao_pinhua = HermesCalculator.pinhuaquxian(processAngleListList, 0 + 1, 5, 26);
            List<int> xiaotuijiajiao_max = HermesCalculator.huaxianValueUp(xiaotuijiajiao_pinhua, 10, 26);
            HermesCalculator.printList(xiaotuijiajiao_max, "右大腿的夹角最大值");

            if (xiaotuijiajiao_max.Count < 2)
            {
                return ret;
            }

            //求右大腿的夹角最小值 - 左
            List<int> xiaotuijiajiao_min = HermesCalculator.huaxianValueDown(xiaotuijiajiao_pinhua, 20, 26);
            HermesCalculator.printList(xiaotuijiajiao_min, "右大腿的夹角最小值");

            //骨盆掉落- 右
            List<double> angleList = new List<double>();
            angleList.Add(HermesCalculator.reqCechengWaizhan2(stageEndStateList[0], 0, 1) - HermesCalculator.reqCechengWaizhan2(stageEndStateList[0], 0, 0));
            for (int i = 0; i < xiaotuijiajiao_min.Count; i++)
            {
                if (xiaotuijiajiao_min[i] <= xiaotuijiajiao_max[xiaotuijiajiao_max.Count - 1] && xiaotuijiajiao_min[i] >= xiaotuijiajiao_max[0])
                {
                    //右腿 - 骨盆
                    angleList.Add(processAngleListList[1, 2][xiaotuijiajiao_min[i]] - processAngleListList[1, 0][xiaotuijiajiao_min[i]]);
                    Console.WriteLine("1： " + (float)processAngleListList[1, 2][xiaotuijiajiao_min[i]]);
                    Console.WriteLine("2： " + (float)processAngleListList[1, 0][xiaotuijiajiao_min[i]]);
                }
            }
            HermesCalculator.printListDouble(angleList, "骨盆掉落 - 右");
            double[] xxxx = HermesCalculator.calMaxMinMeanVar(angleList, 0, angleList.Count - 1);
            Console.WriteLine("骨盆掉落- 右 - 最大值： " + (float)(xxxx[0] - angleList[0]));
            Console.WriteLine("骨盆掉落- 右 - 最小值： " + (float)(xxxx[1] - angleList[0]));
            float max = (float)(xxxx[0] - angleList[0]);
            float min = (float)(xxxx[1] - angleList[0]);
            if (Math.Abs(max) > Math.Abs(min))
            {
                //骨盆右侧掉落1008
                ret.Add("1008", max);
            }
            else
            {
                //骨盆右侧掉落1008
                ret.Add("1008", min);
            }

            //骨盆旋转 - 右
            double[] xxx = HermesCalculator.calMaxMinMeanVar(processAngleListList[0 + 1, 3], 0, processAngleListList[0 + 1, 3].Count - 1);
            Console.WriteLine("骨盆旋转 - 右 - 最大值： " + (float)(xxx[0] - HermesCalculator.reqCechengYaobuZXuanzhuanRight(stageEndStateList[0], 0, 0)) + ' ' +  (float)(xxx[0]) );
            Console.WriteLine("骨盆旋转 - 右 - 最小值： " + (float)(xxx[1] - HermesCalculator.reqCechengYaobuZXuanzhuanRight(stageEndStateList[0], 0, 0)) + ' ' + (float)(xxx[1]));
            max = (float)(xxx[0] - HermesCalculator.reqCechengYaobuZXuanzhuanRight(stageEndStateList[0], 0, 0));
            min = (float)(xxx[1] - HermesCalculator.reqCechengYaobuZXuanzhuanRight(stageEndStateList[0], 0, 0));
            if (Math.Abs(max) > Math.Abs(min))
            {
                //骨盆右侧歪斜1010
                ret.Add("1010", max);
            }
            else
            {
                //骨盆右侧歪斜1010
                ret.Add("1010", min);
            }

            if (HermesNewTest.m_tezhengDic_all.ContainsKey("CeMianChengYouTuiTaiTui") == true)
            {
                HermesNewTest.m_tezhengDic_all["CeMianChengYouTuiTaiTui"] = ret;
            }
            else
            {
                HermesNewTest.m_tezhengDic_all.Add("CeMianChengYouTuiTaiTui", ret);
            }

            return ret;
        }


    }     //状态检测器-侧面撑右腿抬腿3次

    public class HermesNewTest
    {
        public enum TestMathodName
        {
            DaBuZou = 0,
            ShenDun = 1,
            ShuangTuiBingLongXiaDun = 2,
            ZuoCeDanTuiDun = 3,
            YouCeDanTuiDun = 4,
            ZuoCeDanTuiQuKuanShenXi = 5,
            YouCeDanTuiQuKuanShenXi = 6,
            ShuangShouZuoCeDanTuiFuQiao = 7,
            ShuangShouYouCeDanTuiFuQiao = 8,
            ZuoCeDanJiaoZhiCheng = 9,
            YouCeDanJiaoZhiCheng = 10,
            FuWoWeiZuoCeQuXiHouTaiTui = 11,
            FuWoWeiYouCeQuXiHouTaiTui = 12,
            FuWoWeiZuoCeQuXi = 13,
            FuWoWeiYouCeQuXi = 14,
            FuWoZuoCeXiaoTuiDaKai = 15,
            ZuoZiZuoCeSiZiCeShi = 16,
            ZuoZiYouCeSiZiCeShi = 17,
            ZuoZiZuoCeZhiTuiNeiShou = 18,
            ZuoZiYouCeZhiTuiNeiShou = 19,
            CeMianChengZuoTuiTaiTui = 20,
            CeMianChengYouTuiTaiTui = 21,
        }
        //单一化
        public static HermesNewTest instant;
        //动作自动/手动结束(0/1) int
        public int m_automation;
        //动作特征  (字典)
        public Dictionary<string, float> m_tezheng;
        //进度条(0-1) float
        public float m_jindutiao;
        //网络情况正常/异常(0/1) int
        public int m_wangluo;
        //开始计时/结束计时（0/1）int
        public int m_jishi;
        //计时时间 float
        public int m_timeDuration;
        //阶段提示 （0/1）int
        public int m_tipFlag;
        //阶段提示内容 string
        public string m_tipContent;
        //准备阶段是否采集成功（0/1）int
        public int m_prepFlag;
        //动作成功与否（-1/0/1）int
        public int m_successFlag;
        //当前方法
        public TestMathodName m_methodName;
        //特征字典总表
        public static Dictionary<string, Dictionary<string, float>> m_tezhengDic_all = new Dictionary<string, Dictionary<string, float>>();

        //测试方法同类
        public HermesStateDetctor m_object;
        ////测试方法示例-左侧单腿屈髋伸膝
        //HermesStateDetctorForZuoCeDanTuiQuKuanShenXi _HermesStateDetctorForZuoCeDanTuiQuKuanShenXi;
        ////测试方法示例-右侧单腿屈髋伸膝
        //HermesStateDetctorForYouCeDanTuiQuKuanShenXi _HermesStateDetctorForYouCeDanTuiQuKuanShenXi;
        

        //最后时刻状态
        public float[] prepEndState = new float[4 * 7];

        public HermesNewTest()
        {
            if(instant == null)
            {
                instant = this;
                m_tezhengDic_all = new Dictionary<string, Dictionary<string, float>>();
            }
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
            m_wangluo = 0;
            m_tezheng = new Dictionary<string, float>();
        }

        public void reset(TestMathodName index)
        {
            m_methodName = index;
            //基本参数
            m_jindutiao = 0;
            m_jishi = 1;
            m_timeDuration = 0;
            m_tipFlag = 0;
            m_tipContent = "";
            m_prepFlag = 0;
            m_successFlag = 0;
            m_wangluo = 0;
            m_tezheng = new Dictionary<string, float>();
            //中转站
            switch (m_methodName)                      //需要添加
            {
                case TestMathodName.DaBuZou:
                    m_automation = 1;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForZhengChangZou();
                    m_object.reset();
                    break;
                case TestMathodName.ShenDun:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForShenDun();
                    m_object.reset();
                    break;
                case TestMathodName.ShuangTuiBingLongXiaDun:
                    m_automation = 0;
                    m_wangluo = 0;
                    break;
                case TestMathodName.ZuoCeDanTuiDun:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForZuoCeDanTuiDun();
                    m_object.reset();
                    break;
                case TestMathodName.YouCeDanTuiDun:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForYouCeDanTuiDun();
                    m_object.reset();
                    break;
                case TestMathodName.ZuoCeDanTuiQuKuanShenXi:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForZuoCeDanTuiQuKuanShenXi();
                    m_object.reset();
                    break;
                case TestMathodName.YouCeDanTuiQuKuanShenXi:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForYouCeDanTuiQuKuanShenXi();
                    m_object.reset();
                    break;
                case TestMathodName.ShuangShouZuoCeDanTuiFuQiao:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForShuangShouZuoCeDanTuiFuQiao();
                    m_object.reset();
                    break;
                case TestMathodName.ShuangShouYouCeDanTuiFuQiao:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForShuangShouYouCeDanTuiFuQiao();
                    m_object.reset();
                    break;
                case TestMathodName.ZuoCeDanJiaoZhiCheng:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForZuoCeDanJiaoZhiCheng();
                    m_object.reset();
                    break;
                case TestMathodName.YouCeDanJiaoZhiCheng:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForYouCeDanJiaoZhiCheng();
                    m_object.reset();
                    break;

                case TestMathodName.FuWoWeiZuoCeQuXiHouTaiTui:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForFuWoWeiZuoCeQuXiHouTaiTui();
                    m_object.reset();
                    break;
                case TestMathodName.FuWoWeiYouCeQuXiHouTaiTui:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForFuWoWeiYouCeQuXiHouTaiTui();
                    m_object.reset();
                    break;
                case TestMathodName.FuWoWeiZuoCeQuXi:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForFuWoWeiZuoCeQuXi();
                    m_object.reset();
                    break;
                case TestMathodName.FuWoWeiYouCeQuXi:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForFuWoWeiYouCeQuXi();
                    m_object.reset();
                    break;

                case TestMathodName.FuWoZuoCeXiaoTuiDaKai:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForFuWoZuoCeXiaoTuiDaKai();
                    m_object.reset();
                    break;
                case TestMathodName.ZuoZiZuoCeSiZiCeShi:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForZuoZiZuoCeSiZiCeShi();
                    m_object.reset();
                    break;
                case TestMathodName.ZuoZiYouCeSiZiCeShi:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForZuoZiYouCeSiZiCeShi();
                    m_object.reset();
                    break;

                case TestMathodName.ZuoZiZuoCeZhiTuiNeiShou:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForZuoZiZuoCeZhiTuiNeiShou();
                    m_object.reset();
                    break;
                case TestMathodName.ZuoZiYouCeZhiTuiNeiShou:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForZuoZiYouCeZhiTuiNeiShou();
                    m_object.reset();
                    break;

                case TestMathodName.CeMianChengZuoTuiTaiTui:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForCeMianChengZuoTuiTaiTui();
                    m_object.reset();
                    break;
                case TestMathodName.CeMianChengYouTuiTaiTui:
                    m_automation = 0;
                    m_wangluo = 0;
                    m_object = new HermesStateDetctorForCeMianChengYouTuiTaiTui();
                    m_object.reset();
                    break;
                default:
                    break;
            }
        }   //添加

        public void resetTipFlag()
        {
            m_tipFlag = 0;
            m_object.resetTipFlag();
        }

        void calculationSingleTimeForZhengChangZou(float[] float_array, int lineIndex, int isPrepOrAction, int delayTime_10ms)
        {
            //正常走
            //状态检测器
            //存储当前状态，保存状态触发条件函数，保存状态结束条件函数（满足结束条件/超时）
            if (isPrepOrAction == 0)
            {
                //准备阶段
                m_object.calcPrep(float_array, lineIndex);
                //基本参数
                m_jindutiao = m_object.m_jindutiao;
                m_jishi = m_object.m_jishi;
                m_timeDuration = m_object.m_timeDuration;
                m_tipFlag = m_object.m_tipFlag;
                m_tipContent = m_object.m_tipContent;
                m_prepFlag = m_object.m_prepFlag;
                m_successFlag = m_object.m_successFlag;
            }
            else if (isPrepOrAction == 1)
            {
                //动作阶段
                m_object.calc(float_array, lineIndex, delayTime_10ms);
                //基本参数
                m_jindutiao = m_object.m_jindutiao;
                m_jishi = m_object.m_jishi;
                m_timeDuration = m_object.m_timeDuration;
                m_tipFlag = m_object.m_tipFlag;
                m_tipContent = m_object.m_tipContent;
                m_prepFlag = m_object.m_prepFlag;
                m_successFlag = m_object.m_successFlag;
            }
        }

        void calculationSingleTimeForNormal(float[] float_array, int lineIndex, int isPrepOrAction, int delayTime_10ms)
        {
            //左侧单腿屈髋伸膝
            //状态检测器
            //存储当前状态，保存状态触发条件函数，保存状态结束条件函数（满足结束条件/超时）
            if (isPrepOrAction == 0)
            {
                //准备阶段
                m_object.calcPrep(float_array, lineIndex);
                //基本参数
                m_jindutiao = m_object.m_jindutiao;
                m_jishi = m_object.m_jishi;
                m_timeDuration = m_object.m_timeDuration;
                m_tipFlag = m_object.m_tipFlag;
                m_tipContent = m_object.m_tipContent;
                m_prepFlag = m_object.m_prepFlag;
                m_successFlag = m_object.m_successFlag;
            }
            else if (isPrepOrAction == 1)
            {
                //动作阶段
                m_object.calc(float_array, lineIndex, delayTime_10ms);
                //基本参数
                m_jindutiao = m_object.m_jindutiao;
                m_jishi = m_object.m_jishi;
                m_timeDuration = m_object.m_timeDuration;
                m_tipFlag = m_object.m_tipFlag;
                m_tipContent = m_object.m_tipContent;
                m_prepFlag = m_object.m_prepFlag;
                m_successFlag = m_object.m_successFlag;
            }
        }

        public void calculationSingleTime(float[] float_array, int lineIndex)
        {
            int type = 1;
            //中转站
            switch (m_methodName)
            {
                case TestMathodName.DaBuZou:
                    calculationSingleTimeForZhengChangZou(float_array, lineIndex, type, 100 * 80);
                    break;
                case TestMathodName.ShenDun:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                case TestMathodName.ShuangTuiBingLongXiaDun:
                    
                    break;
                case TestMathodName.ZuoCeDanTuiDun:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.YouCeDanTuiDun:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.ZuoCeDanTuiQuKuanShenXi:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.YouCeDanTuiQuKuanShenXi:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.ShuangShouZuoCeDanTuiFuQiao:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                case TestMathodName.ShuangShouYouCeDanTuiFuQiao:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                case TestMathodName.ZuoCeDanJiaoZhiCheng:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 100);
                    break;
                case TestMathodName.YouCeDanJiaoZhiCheng:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 100);
                    break;

                case TestMathodName.FuWoWeiZuoCeQuXiHouTaiTui:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                case TestMathodName.FuWoWeiYouCeQuXiHouTaiTui:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                case TestMathodName.FuWoWeiZuoCeQuXi:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                case TestMathodName.FuWoWeiYouCeQuXi:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                case TestMathodName.FuWoZuoCeXiaoTuiDaKai:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;

                case TestMathodName.ZuoZiZuoCeSiZiCeShi:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                case TestMathodName.ZuoZiYouCeSiZiCeShi:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;

                case TestMathodName.ZuoZiZuoCeZhiTuiNeiShou:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                case TestMathodName.ZuoZiYouCeZhiTuiNeiShou:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;

                case TestMathodName.CeMianChengZuoTuiTaiTui:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                case TestMathodName.CeMianChengYouTuiTaiTui:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 20);
                    break;
                default:
                    break;
            }
        }     //添加

        public void prep(float[] float_array, int lineIndex)
        {
            //记录下最后时刻的状态
            //验证状态是否达标，一秒钟防抖动
            //验证状态是否达标,是否在规定的范围内
            int type = 0;
            //中转站
            switch (m_methodName)
            {
                case TestMathodName.DaBuZou:
                    calculationSingleTimeForZhengChangZou(float_array, lineIndex, type, 100 * 80);
                    break;
                case TestMathodName.ShenDun:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 15);
                    break;
                case TestMathodName.ZuoCeDanTuiQuKuanShenXi:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.YouCeDanTuiQuKuanShenXi:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.ShuangShouZuoCeDanTuiFuQiao:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.ShuangShouYouCeDanTuiFuQiao:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.ZuoCeDanJiaoZhiCheng:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.YouCeDanJiaoZhiCheng:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.ZuoCeDanTuiDun:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                case TestMathodName.YouCeDanTuiDun:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
                default:
                    calculationSingleTimeForNormal(float_array, lineIndex, type, 100 * 25);
                    break;
            }
        }       

        public int finalResult(float[] float_array, int lineIndex)
        {
            switch (m_methodName)
            {
                case TestMathodName.DaBuZou:
                    m_tezheng = m_object.getTezheng();
                    break;
                default:
                    m_tezheng = m_object.getTezheng();
                    break;
            }
            return 0;
        }

    }  //新版测试，主要类
}
