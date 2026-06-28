package script.hist_cmn
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.net.URLRequest;
   import script.xcmn_font.smb_font;
   
   public class start_list_base extends MovieClip
   {
      
      private const MAX_LIST_NUM:* = 4;
      
      private const MAX_BATTLE_NUM:* = 4;
      
      private const CCD_TEXT_SCROLL_WIDTH:Number = 580;
      
      private const CCD_RANK_TBL:Array = ["s","a","b","c","d"];
      
      public var m_startPointList:Array = new Array();
      
      public var m_index:int;
      
      public var m_battleNum:int;
      
      public var m_totalRankPoint:int;
      
      public var m_playerFace:Array = new Array(this.MAX_BATTLE_NUM);
      
      public var m_enemyFace:Array = new Array(this.MAX_BATTLE_NUM);
      
      public function start_list_base()
      {
         super();
         this.m_index = 0;
         this.m_battleNum = 0;
         this.m_totalRankPoint = 0;
         var _loc1_:int = 0;
         while(_loc1_ < this.MAX_BATTLE_NUM)
         {
            this.m_playerFace[_loc1_] = new ExtendLoader();
            this.m_enemyFace[_loc1_] = new ExtendLoader();
            _loc1_++;
         }
         this.CreateStartPointList();
      }
      
      public function CreateStartPointList() : *
      {
      }
      
      public function SetActive(param1:*) : *
      {
         var _loc3_:MovieClip = null;
         var _loc4_:smb_font = null;
         var _loc5_:smb_font = null;
         var _loc2_:int = 0;
         while(_loc2_ < this.m_startPointList.length)
         {
            _loc3_ = MovieClip(this.m_startPointList[_loc2_]);
            if(_loc3_)
            {
               if(Boolean(param1) && _loc2_ == this.m_index)
               {
                  if(_loc3_.currentLabel != "none")
                  {
                     _loc3_.gotoAndPlay("on");
                  }
                  _loc4_ = smb_font(_loc3_["txt_msg"]);
                  if(_loc4_)
                  {
                     _loc4_.SetTextFieldWidth(this.CCD_TEXT_SCROLL_WIDTH);
                     _loc4_.SetTextScroll(true);
                     _loc4_.PlayTextScroll();
                  }
               }
               else
               {
                  if(_loc3_.currentLabel != "none")
                  {
                     _loc3_.gotoAndStop("off");
                  }
                  _loc5_ = smb_font(_loc3_["txt_msg"]);
                  if(_loc5_)
                  {
                     _loc5_.SetTextScroll(false);
                     _loc5_.SetTextFieldWidth(this.CCD_TEXT_SCROLL_WIDTH);
                     _loc5_.SetTextScroll(true);
                     _loc5_.StopTextScroll();
                  }
               }
            }
            _loc2_++;
         }
      }
      
      public function SetIndexUp() : *
      {
         var _loc1_:int = 0;
         var _loc2_:MovieClip = null;
         if(this.m_startPointList.length > 0)
         {
            _loc1_ = this.m_index;
            if(this.m_startPointList.length > 1)
            {
               ++this.m_index;
               if(this.m_index > this.m_startPointList.length - 1)
               {
                  this.m_index = _loc1_;
               }
               _loc2_ = MovieClip(this.m_startPointList[this.m_index]);
               if(Boolean(_loc2_) && _loc2_.currentLabel == "none")
               {
                  this.m_index = _loc1_;
               }
            }
            if(_loc1_ != this.m_index)
            {
               this.SetActive(true);
            }
         }
      }
      
      public function SetIndexDown() : *
      {
         var _loc1_:int = 0;
         if(this.m_startPointList.length > 0)
         {
            _loc1_ = this.m_index;
            if(this.m_startPointList.length > 1)
            {
               --this.m_index;
               if(this.m_index < 0)
               {
                  this.m_index = 0;
               }
            }
            if(_loc1_ != this.m_index)
            {
               this.SetActive(true);
            }
         }
      }
      
      public function SetEnter() : *
      {
         var _loc1_:MovieClip = MovieClip(this.m_startPointList[this.m_index]);
         if(Boolean(_loc1_) && _loc1_.currentLabel != "none")
         {
            _loc1_.gotoAndPlay("enter");
         }
      }
      
      public function GetIndex() : int
      {
         return this.m_index;
      }
      
      public function SetDemoInfo(param1:int, param2:String) : *
      {
         var _loc5_:MovieClip = null;
         var _loc6_:smb_font = null;
         var _loc3_:String = "mc_c" + (param1 + 1).toString();
         var _loc4_:MovieClip = MovieClip(this[_loc3_]);
         if(_loc4_)
         {
            _loc4_.gotoAndStop("off");
            _loc5_ = MovieClip(_loc4_["mc_new"]);
            if(_loc5_)
            {
               _loc5_.visible = false;
            }
            _loc6_ = smb_font(_loc4_["txt_msg"]);
            if(_loc6_)
            {
               _loc6_.SetText(param2);
            }
         }
         this.m_index = 0;
      }
      
      public function SetBattleInfo(param1:int, param2:int) : *
      {
         var _loc5_:MovieClip = null;
         var _loc6_:smb_font = null;
         var _loc7_:MovieClip = null;
         var _loc8_:MovieClip = null;
         var _loc9_:String = null;
         var _loc10_:String = null;
         var _loc11_:String = null;
         var _loc12_:HistParam = null;
         var _loc13_:MovieClip = null;
         var _loc14_:URLRequest = null;
         var _loc15_:URLRequest = null;
         var _loc3_:String = "mc_btl" + (param1 + 1).toString();
         var _loc4_:MovieClip = MovieClip(this[_loc3_]);
         if(_loc4_)
         {
            ++this.m_battleNum;
            _loc4_.gotoAndStop("off");
            _loc5_ = MovieClip(_loc4_["mc_new"]);
            if(_loc5_)
            {
               _loc5_.visible = false;
            }
            _loc6_ = smb_font(_loc4_["txt_none"]);
            if(_loc6_)
            {
               _loc6_.visible = false;
            }
            _loc7_ = MovieClip(_loc4_["mc_rslt"]);
            if(_loc7_)
            {
               _loc7_.visible = false;
            }
            _loc8_ = MovieClip(_loc4_["mc_up"]);
            if(_loc8_)
            {
               _loc8_.visible = false;
            }
            _loc12_ = new HistParam();
            if(_loc12_)
            {
               _loc9_ = _loc12_.GetBattleIconInfo(param2,param1,HistParam.ICON_BATTLE_TYPE);
               _loc10_ = _loc12_.GetBattleIconInfo(param2,param1,HistParam.ICON_BATTLE_PLAYER);
               _loc11_ = _loc12_.GetBattleIconInfo(param2,param1,HistParam.ICON_BATTLE_ENEMY);
            }
            _loc13_ = MovieClip(_loc4_["mc_type"]);
            if(_loc13_)
            {
               _loc13_.gotoAndStop(_loc9_);
            }
            _loc14_ = new URLRequest("../charicon_vs/vs_" + _loc10_ + ".xfbin");
            this.m_playerFace[param1].load(_loc14_);
            this.m_playerFace[param1].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            if(_loc4_.dmy_char1)
            {
               _loc4_.dmy_char1.addChild(this.m_playerFace[param1]);
            }
            _loc15_ = new URLRequest("../charicon_vs/vs_" + _loc11_ + ".xfbin");
            this.m_enemyFace[param1].load(_loc15_);
            this.m_enemyFace[param1].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            if(_loc4_.dmy_char2)
            {
               _loc4_.dmy_char2.addChild(this.m_enemyFace[param1]);
            }
         }
      }
      
      public function SetSaveDataInfo(param1:int, param2:String, param3:Boolean, param4:Boolean, param5:Boolean, param6:int, param7:Boolean) : *
      {
         var _loc9_:Boolean = false;
         var _loc10_:MovieClip = null;
         var _loc11_:smb_font = null;
         var _loc12_:MovieClip = null;
         var _loc13_:MovieClip = null;
         var _loc8_:MovieClip = MovieClip(this.m_startPointList[param1]);
         if(_loc8_)
         {
            _loc9_ = false;
            if(_loc8_["mc_type"])
            {
               _loc9_ = true;
            }
            if(_loc9_)
            {
               if(param3)
               {
                  _loc10_ = MovieClip(_loc8_["mc_new"]);
                  if(_loc10_)
                  {
                     if(param4 == false)
                     {
                        _loc10_.visible = true;
                     }
                     else
                     {
                        _loc10_.visible = false;
                     }
                  }
                  _loc12_ = MovieClip(_loc8_["mc_rslt"]);
                  if(_loc12_)
                  {
                     if(param5)
                     {
                        _loc12_.visible = true;
                        _loc12_.gotoAndStop(this.CCD_RANK_TBL[param6]);
                        _loc13_ = MovieClip(_loc8_["mc_up"]);
                        if((Boolean(_loc13_)) && param7)
                        {
                           _loc13_.visible = true;
                        }
                        switch(param6)
                        {
                           case HistParam.CCD_BATTLE_RANK_S:
                              this.m_totalRankPoint += 4;
                              break;
                           case HistParam.CCD_BATTLE_RANK_A:
                              this.m_totalRankPoint += 3;
                              break;
                           case HistParam.CCD_BATTLE_RANK_B:
                              this.m_totalRankPoint += 2;
                              break;
                           case HistParam.CCD_BATTLE_RANK_C:
                              this.m_totalRankPoint += 1;
                              break;
                           case HistParam.CCD_BATTLE_RANK_D:
                              this.m_totalRankPoint += 0;
                        }
                     }
                     else
                     {
                        _loc12_.visible = false;
                     }
                  }
               }
               else
               {
                  _loc11_ = smb_font(_loc8_["txt_none"]);
                  if(_loc11_)
                  {
                     _loc11_.SetText(param2);
                     _loc11_.visible = true;
                  }
                  _loc8_.gotoAndStop("none");
               }
            }
            else if(param3)
            {
               _loc10_ = MovieClip(_loc8_["mc_new"]);
               if(_loc10_)
               {
                  if(param4 == false)
                  {
                     _loc10_.visible = true;
                  }
                  else
                  {
                     _loc10_.visible = false;
                  }
               }
            }
            else
            {
               _loc11_ = smb_font(_loc8_["txt_msg"]);
               if(_loc11_)
               {
                  _loc11_.SetText(param2);
               }
               _loc8_.gotoAndStop("none");
            }
         }
      }
      
      public function GetStartPointNum() : int
      {
         return this.m_startPointList.length;
      }
      
      public function IsBattle() : Boolean
      {
         var _loc1_:Boolean = false;
         var _loc2_:MovieClip = MovieClip(this.m_startPointList[this.m_index]);
         if(Boolean(_loc2_) && Boolean(_loc2_["mc_type"]))
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      public function ResetTotalRank() : *
      {
         this.m_battleNum = 0;
         this.m_totalRankPoint = 0;
      }
      
      public function GetTotalRank() : int
      {
         var _loc1_:int = 0;
         var _loc2_:int = HistParam.CCD_BATTLE_RANK_NONE;
         if(this.m_battleNum > 0)
         {
            _loc1_ = this.m_totalRankPoint / this.m_battleNum;
            if(_loc1_ >= 4)
            {
               _loc2_ = HistParam.CCD_BATTLE_RANK_S;
            }
            else if(_loc1_ < 4 && _loc1_ >= 3)
            {
               _loc2_ = HistParam.CCD_BATTLE_RANK_A;
            }
            else if(_loc1_ < 3 && _loc1_ >= 2)
            {
               _loc2_ = HistParam.CCD_BATTLE_RANK_B;
            }
            else if(_loc1_ < 2 && _loc1_ >= 1)
            {
               _loc2_ = HistParam.CCD_BATTLE_RANK_C;
            }
            else
            {
               _loc2_ = HistParam.CCD_BATTLE_RANK_D;
            }
         }
         return _loc2_;
      }
   }
}

