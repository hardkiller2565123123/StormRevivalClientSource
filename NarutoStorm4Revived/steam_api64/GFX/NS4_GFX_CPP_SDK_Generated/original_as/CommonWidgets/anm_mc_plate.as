package script.collect_vo
{
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol3")]
   public class anm_mc_plate extends MovieClip
   {
      
      public static const CCD_PLATE_NUM:int = 13;
      
      public static const CCD_VO1_TEXT_WIDTH:int = 930;
      
      public var mc_bar_00:anm_mc_bar;
      
      public var mc_bar_01:anm_mc_bar;
      
      public var mc_bar_02:anm_mc_bar;
      
      public var mc_bar_03:anm_mc_bar;
      
      public var mc_bar_04:anm_mc_bar;
      
      public var mc_bar_05:anm_mc_bar;
      
      public var mc_bar_06:anm_mc_bar;
      
      public var mc_bar_07:anm_mc_bar;
      
      public var mc_bar_08:anm_mc_bar;
      
      public var mc_bar_09:anm_mc_bar;
      
      public var mc_bar_10:anm_mc_bar;
      
      public var mc_bar_11:anm_mc_bar;
      
      public var mc_bar_12:anm_mc_bar;
      
      private var m_plateCtn:Array = new Array();
      
      private var m_platePosY:Array = new Array();
      
      private var m_plateNoCtn:Array = new Array();
      
      private var m_topPlateNo:int = 0;
      
      private var m_noTxt:String = "";
      
      private var m_rearity:Array = ["n","r","sr","ur","sc"];
      
      private var m_closeTxt:String = "";
      
      public function anm_mc_plate()
      {
         super();
         var _loc1_:int = 0;
         while(_loc1_ < CCD_PLATE_NUM)
         {
            this.m_plateCtn.push(anm_mc_bar(getChildByName("mc_bar_" + String("00" + _loc1_).slice(-2))));
            this.m_plateCtn[_loc1_].m_new_1.visible = false;
            this.m_platePosY.push(this.m_plateCtn[_loc1_].y);
            this.m_plateNoCtn.push(_loc1_);
            _loc1_++;
         }
         this.m_noTxt = String(ExternalInterface.call("MessageConvert","collect_infocard_044"));
         this.m_closeTxt = String(ExternalInterface.call("MessageConvert","collect_infocard_068"));
      }
      
      public function ResetPlateInfo(param1:int, param2:Array, param3:Boolean) : *
      {
         var _loc5_:MovieClip = null;
         var _loc6_:Array = null;
         var _loc4_:int = 0;
         while(_loc4_ < CCD_PLATE_NUM)
         {
            if(param2[_loc4_].no == -1)
            {
               this.m_plateCtn[_loc4_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_NAME,param2[_loc4_].openFlag);
               this.m_plateCtn[_loc4_].m_name.SetText(param2[_loc4_].mesID);
            }
            else
            {
               if(param1 == _loc4_)
               {
                  if(param3 && Boolean(param2[_loc4_].openFlag))
                  {
                     this.m_plateCtn[_loc4_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_ON_CHECK,param2[_loc4_].openFlag);
                  }
                  else
                  {
                     this.m_plateCtn[_loc4_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_ON,param2[_loc4_].openFlag);
                  }
                  param2[_loc4_].newIcon = false;
               }
               else if(param3 && Boolean(param2[_loc4_].openFlag))
               {
                  this.m_plateCtn[_loc4_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_OFF_CHECK,param2[_loc4_].openFlag);
               }
               else
               {
                  this.m_plateCtn[_loc4_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_OFF,param2[_loc4_].openFlag);
               }
               _loc5_ = null;
               this.m_plateCtn[_loc4_].m_num.SetText(this.m_noTxt);
               _loc6_ = new Array(0);
               _loc6_.push(String("000" + param2[_loc4_].no).slice(-3));
               this.m_plateCtn[_loc4_].m_num.ReplaceTextList(_loc6_);
               if(param2[_loc4_].openFlag)
               {
                  this.m_plateCtn[_loc4_].m_vo_1.SetText(param2[_loc4_].voiceID[0]);
                  this.m_plateCtn[_loc4_].m_rearity.gotoAndStop(this.m_rearity[param2[_loc4_].rarity]);
               }
               else
               {
                  this.m_plateCtn[_loc4_].m_vo_1.SetText(this.m_closeTxt);
               }
               if(this.m_plateCtn[_loc4_].m_vo_1.GetTextFieldWidth() > CCD_VO1_TEXT_WIDTH)
               {
                  this.m_plateCtn[_loc4_].m_vo_1.SetTextScroll(true);
               }
               else
               {
                  this.m_plateCtn[_loc4_].m_vo_1.SetTextScroll(false);
               }
               if(param3)
               {
                  if(param2[_loc4_].openFlag)
                  {
                     if(param2[_loc4_].selected)
                     {
                        this.m_plateCtn[_loc4_].m_check_1.gotoAndStop("check");
                     }
                     else
                     {
                        this.m_plateCtn[_loc4_].m_check_1.gotoAndStop("empty");
                     }
                  }
               }
               this.m_plateCtn[_loc4_].m_new_1.visible = param2[_loc4_].newIcon;
               if(param1 == _loc4_)
               {
                  this.m_plateCtn[_loc4_].m_vo_1.PlayTextScroll();
               }
               else
               {
                  this.m_plateCtn[_loc4_].m_vo_1.StopTextScroll();
               }
            }
            _loc4_++;
         }
      }
      
      public function SetPlateInfo(param1:int, param2:int, param3:int, param4:int, param5:Array, param6:Boolean) : *
      {
         var _loc12_:int = 0;
         var _loc13_:int = 0;
         var _loc14_:Array = null;
         if(param2 == param1)
         {
            this.ChangeCursorNoScroll(param3,param4,param5,param6);
            return;
         }
         trace("oldDisp:" + param1 + ", nowDisp:" + param2 + ", nowSel:" + param4);
         var _loc7_:int = param2 - param1;
         var _loc8_:int = _loc7_ > 0 ? 1 : -1;
         var _loc9_:int = Math.abs(_loc7_);
         var _loc10_:Array = new Array();
         var _loc11_:int = 0;
         while(_loc11_ < CCD_PLATE_NUM)
         {
            if(_loc8_ > 0)
            {
               if(_loc11_ < _loc9_)
               {
                  _loc10_.push(this.m_plateCtn[_loc11_]);
               }
               else
               {
                  this.m_plateCtn[_loc11_].y = this.m_platePosY[_loc11_ - _loc9_];
                  this.m_plateCtn[_loc11_ - _loc9_] = this.m_plateCtn[_loc11_];
               }
            }
            else if(_loc11_ < _loc9_)
            {
               _loc10_.push(this.m_plateCtn[CCD_PLATE_NUM - _loc11_ - 1]);
            }
            else
            {
               _loc12_ = CCD_PLATE_NUM - _loc11_ - 1;
               this.m_plateCtn[_loc12_].y = this.m_platePosY[_loc12_ + _loc9_];
               this.m_plateCtn[_loc12_ + _loc9_] = this.m_plateCtn[_loc12_];
            }
            _loc11_++;
         }
         _loc11_ = 0;
         while(_loc11_ < _loc10_.length)
         {
            _loc13_ = _loc8_ > 0 ? int(CCD_PLATE_NUM - _loc11_ - 1) : _loc11_;
            if(param5[_loc13_].no == -1)
            {
               _loc10_[_loc11_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_NAME,param5[_loc13_].openFlag);
               _loc10_[_loc11_].m_name.SetText(param5[_loc13_].mesID);
            }
            else
            {
               if(param6 && Boolean(param5[_loc13_].openFlag))
               {
                  _loc10_[_loc11_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_OFF_CHECK,param5[_loc13_].openFlag);
               }
               else
               {
                  _loc10_[_loc11_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_OFF,param5[_loc13_].openFlag);
               }
               trace("plateName:" + param5[_loc13_].voiceID[0],"ctnNo:" + _loc11_,"plateNo:" + _loc13_);
               "openFlg:" + param5[_loc13_].openFlag;
               _loc10_[_loc11_].m_num.SetText(this.m_noTxt);
               _loc14_ = new Array(0);
               _loc14_.push(String("000" + param5[_loc13_].no).slice(-3));
               _loc10_[_loc11_].m_num.ReplaceTextList(_loc14_);
               if(param5[_loc13_].openFlag)
               {
                  _loc10_[_loc11_].m_vo_1.SetText(param5[_loc13_].voiceID[0]);
                  _loc10_[_loc11_].m_rearity.gotoAndStop(this.m_rearity[param5[_loc13_].rarity]);
               }
               else
               {
                  _loc10_[_loc11_].m_vo_1.SetText(this.m_closeTxt);
                  trace("rearityVisible:" + _loc10_[_loc11_].m_rearity.visible);
               }
               if(_loc10_[_loc11_].m_vo_1.GetTextFieldWidth() > CCD_VO1_TEXT_WIDTH)
               {
                  _loc10_[_loc11_].m_vo_1.SetTextScroll(true);
               }
               else
               {
                  _loc10_[_loc11_].m_vo_1.SetTextScroll(false);
               }
            }
            this.m_plateCtn[_loc13_] = _loc10_[_loc11_];
            this.m_plateCtn[_loc13_].y = this.m_platePosY[_loc13_];
            _loc11_++;
         }
         param3 -= _loc7_;
         _loc11_ = 0;
         while(_loc11_ < CCD_PLATE_NUM)
         {
            if(_loc11_ == param4)
            {
               if(param6 && Boolean(param5[_loc11_].openFlag))
               {
                  this.m_plateCtn[_loc11_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_ON_CHECK,param5[_loc11_].openFlag);
               }
               else
               {
                  this.m_plateCtn[_loc11_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_ON,param5[_loc11_].openFlag);
               }
               this.m_plateCtn[_loc11_].m_vo_1.PlayTextScroll();
               param5[_loc11_].newIcon = false;
            }
            else
            {
               trace("OldSelect:" + param3,"moveVol:" + _loc7_);
               if(_loc11_ == param3)
               {
                  if(param6 && Boolean(param5[_loc11_].openFlag))
                  {
                     this.m_plateCtn[_loc11_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_OFF_CHECK,param5[_loc11_].openFlag);
                  }
                  else
                  {
                     this.m_plateCtn[_loc11_].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_OFF,param5[_loc11_].openFlag);
                  }
                  trace("OldplateName:" + param5[_loc11_].voiceID[0],"ctnNo:" + _loc11_,"OpenFlg:" + param5[_loc11_].openFlag);
               }
               this.m_plateCtn[_loc11_].m_vo_1.StopTextScroll();
            }
            if(param6)
            {
               if(param5[_loc11_].openFlag)
               {
                  trace("ScrollPlateSet.VoiceSelected:" + param5[_loc11_].selected);
                  if(param5[_loc11_].selected)
                  {
                     this.m_plateCtn[_loc11_].m_check_1.gotoAndStop("check");
                  }
                  else
                  {
                     this.m_plateCtn[_loc11_].m_check_1.gotoAndStop("empty");
                  }
               }
            }
            this.m_plateCtn[_loc11_].m_new_1.visible = param5[_loc11_].newIcon;
            _loc11_++;
         }
      }
      
      public function SetCheckMark(param1:Array, param2:Boolean) : *
      {
         var _loc3_:int = 0;
         while(_loc3_ < CCD_PLATE_NUM)
         {
            if(param2)
            {
               if(param1[_loc3_].openFlag)
               {
                  if(param1[_loc3_].selected)
                  {
                     this.m_plateCtn[_loc3_].m_check_1.gotoAndStop("check");
                  }
                  else
                  {
                     this.m_plateCtn[_loc3_].m_check_1.gotoAndStop("empty");
                  }
               }
            }
            _loc3_++;
         }
      }
      
      private function ChangeCursorNoScroll(param1:int, param2:int, param3:Array, param4:Boolean) : *
      {
         if(param4 && Boolean(param3[param1].openFlag))
         {
            this.m_plateCtn[param1].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_OFF_CHECK,param3[param1].openFlag);
         }
         else
         {
            this.m_plateCtn[param1].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_OFF,param3[param1].openFlag);
         }
         if(param4 && Boolean(param3[param2].openFlag))
         {
            this.m_plateCtn[param2].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_ON_CHECK,param3[param2].openFlag);
         }
         else
         {
            this.m_plateCtn[param2].ChangePlate(anm_mc_bar.CCD_PLATE_TYPE_ON,param3[param2].openFlag);
         }
         this.m_plateCtn[param1].m_vo_1.StopTextScroll();
         this.m_plateCtn[param2].m_vo_1.PlayTextScroll();
         param3[param2].newIcon = false;
         var _loc5_:int = 0;
         while(_loc5_ < CCD_PLATE_NUM)
         {
            if(param4)
            {
               if(param3[_loc5_].openFlag)
               {
                  if(param3[_loc5_].selected)
                  {
                     this.m_plateCtn[_loc5_].m_check_1.gotoAndStop("check");
                  }
                  else
                  {
                     this.m_plateCtn[_loc5_].m_check_1.gotoAndStop("empty");
                  }
               }
            }
            this.m_plateCtn[_loc5_].m_new_1.visible = param3[_loc5_].newIcon;
            _loc5_++;
         }
      }
   }
}

