package script.duel_boss_sf
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol20")]
   public class nut_sf extends MovieClip
   {
      
      public var mc_l1:MovieClip;
      
      public var mc_l2:MovieClip;
      
      public var mc_l3:MovieClip;
      
      public var mc_l4:MovieClip;
      
      public var mc_l5:MovieClip;
      
      public var mc_s1:MovieClip;
      
      public var mc_s10:MovieClip;
      
      public var mc_s2:MovieClip;
      
      public var mc_s3:MovieClip;
      
      public var mc_s4:MovieClip;
      
      public var mc_s5:MovieClip;
      
      public var mc_s6:MovieClip;
      
      public var mc_s7:MovieClip;
      
      public var mc_s8:MovieClip;
      
      public var mc_s9:MovieClip;
      
      private const CCD_STARS_L_MAX:* = 5;
      
      private const CCD_STARS_S_MAX:* = 10;
      
      private var m_starsL:Array = new Array();
      
      private var m_starLAnm:Array = new Array();
      
      private var m_starsS:Array = new Array();
      
      private var m_starSAnm:Array = new Array();
      
      private var m_currentStarNum:int = 0;
      
      private var m_sfOpenNum:int = 0;
      
      private var m_maxNum:int = 0;
      
      private var m_isAdvanceNum10:Boolean = false;
      
      private var m_basePosX_l:Number = 0;
      
      private var m_interval_l:Number = 0;
      
      private var m_basePosX_s:Number = 0;
      
      private var m_interval_s:Number = 0;
      
      public function nut_sf()
      {
         super();
         this.gotoAndStop("in");
         var _loc1_:int = 0;
         this.m_starsL[0] = MovieClip(this["mc_l1"]);
         this.m_starsL[1] = MovieClip(this["mc_l2"]);
         this.m_starsL[2] = MovieClip(this["mc_l3"]);
         this.m_starsL[3] = MovieClip(this["mc_l4"]);
         this.m_starsL[4] = MovieClip(this["mc_l5"]);
         _loc1_ = 0;
         while(_loc1_ < this.m_starsL.length)
         {
            this.m_starsL[_loc1_].gotoAndStop("in");
            this.m_starLAnm[_loc1_] = anm_sf(this.m_starsL[_loc1_]["mc_l"]);
            if(this.m_starLAnm[_loc1_])
            {
               this.m_starLAnm[_loc1_].gotoAndStop("off");
               MovieClip(this.m_starLAnm[_loc1_]["mc_mark"]).visible = false;
            }
            _loc1_++;
         }
         this.m_starsS[0] = MovieClip(this["mc_s1"]);
         this.m_starsS[1] = MovieClip(this["mc_s2"]);
         this.m_starsS[2] = MovieClip(this["mc_s3"]);
         this.m_starsS[3] = MovieClip(this["mc_s4"]);
         this.m_starsS[4] = MovieClip(this["mc_s5"]);
         this.m_starsS[5] = MovieClip(this["mc_s6"]);
         this.m_starsS[6] = MovieClip(this["mc_s7"]);
         this.m_starsS[7] = MovieClip(this["mc_s8"]);
         this.m_starsS[8] = MovieClip(this["mc_s9"]);
         this.m_starsS[9] = MovieClip(this["mc_s10"]);
         _loc1_ = 0;
         while(_loc1_ < this.m_starsS.length)
         {
            this.m_starsS[_loc1_].gotoAndStop("in");
            this.m_starSAnm[_loc1_] = anm_sf(this.m_starsS[_loc1_]["mc_l"]);
            if(this.m_starSAnm[_loc1_])
            {
               this.m_starSAnm[_loc1_].gotoAndStop("off");
               MovieClip(this.m_starSAnm[_loc1_]["mc_mark"]).visible = false;
            }
            _loc1_++;
         }
         this.m_basePosX_l = this.m_starsL[0].x;
         this.m_interval_l = this.m_starsL[1].x - this.m_starsL[0].x;
         this.m_basePosX_s = this.m_starsS[0].x;
         this.m_interval_s = this.m_starsS[1].x - this.m_starsS[0].x;
      }
      
      public function PlayInTotalStars(param1:int, param2:int) : *
      {
         var _loc14_:MovieClip = null;
         var _loc15_:MovieClip = null;
         this.m_sfOpenNum = param1;
         this.m_maxNum = param2;
         var _loc3_:int = this.m_currentStarNum / 10;
         var _loc4_:int = this.m_currentStarNum % 10;
         var _loc5_:int = this.m_maxNum / 10;
         var _loc6_:int = this.m_maxNum % 10;
         var _loc7_:int = this.m_sfOpenNum / 10;
         var _loc8_:int = this.m_sfOpenNum % 10;
         var _loc9_:int = 0;
         var _loc10_:Number = this.m_interval_l * 0.5;
         var _loc11_:Number = this.m_basePosX_l + _loc10_ * (5 - _loc5_);
         _loc9_ = 0;
         while(_loc9_ < this.m_starsL.length)
         {
            if(_loc9_ < _loc5_)
            {
               this.m_starsL[_loc9_].visible = true;
            }
            else
            {
               this.m_starsL[_loc9_].visible = false;
            }
            this.m_starsL[_loc9_].x = _loc11_ + this.m_interval_l * _loc9_;
            this.m_starsL[_loc9_].gotoAndPlay("in");
            _loc14_ = MovieClip(this.m_starLAnm[_loc9_]["mc_mark"]);
            if(_loc14_)
            {
               if(_loc9_ < _loc7_)
               {
                  _loc14_.visible = true;
               }
               else
               {
                  _loc14_.visible = false;
               }
            }
            _loc9_++;
         }
         var _loc12_:Number = this.m_interval_s * 0.5;
         var _loc13_:Number = this.m_basePosX_s + _loc12_ * (10 - _loc6_);
         _loc9_ = 0;
         while(_loc9_ < this.m_starsS.length)
         {
            if(_loc3_ >= _loc5_)
            {
               if(_loc9_ < _loc6_)
               {
                  this.m_starsS[_loc9_].visible = true;
               }
               else
               {
                  this.m_starsS[_loc9_].visible = false;
               }
               this.m_starsS[_loc9_].x = _loc13_ + this.m_interval_s * _loc9_;
            }
            else
            {
               this.m_starsS[_loc9_].visible = true;
               this.m_starsS[_loc9_].x = this.m_basePosX_s + this.m_interval_s * _loc9_;
            }
            this.m_starsS[_loc9_].gotoAndPlay("in");
            _loc15_ = MovieClip(this.m_starSAnm[_loc9_]["mc_mark"]);
            if(_loc15_)
            {
               if(_loc3_ == _loc7_)
               {
                  if(_loc9_ < _loc8_)
                  {
                     _loc15_.visible = true;
                  }
                  else
                  {
                     _loc15_.visible = false;
                  }
               }
               else if(_loc3_ > _loc7_)
               {
                  _loc15_.visible = false;
               }
               else if(_loc3_ < _loc7_)
               {
                  _loc15_.visible = true;
               }
            }
            _loc9_++;
         }
         addEventListener(Event.ENTER_FRAME,this.UpdateStars);
      }
      
      public function PlayOutTotalStars() : *
      {
         this.SetStarsNumDirect(this.m_currentStarNum);
         var _loc1_:int = 0;
         _loc1_ = 0;
         while(_loc1_ < this.m_starsL.length)
         {
            this.m_starsL[_loc1_].gotoAndPlay("out");
            _loc1_++;
         }
         _loc1_ = 0;
         while(_loc1_ < this.m_starsS.length)
         {
            this.m_starsS[_loc1_].gotoAndPlay("out");
            _loc1_++;
         }
         removeEventListener(Event.ENTER_FRAME,this.UpdateStars);
      }
      
      public function AddStars(param1:int) : *
      {
         var _loc2_:int = this.m_currentStarNum / 10;
         this.m_currentStarNum += param1;
         if(this.m_currentStarNum > this.m_maxNum)
         {
            this.m_currentStarNum = this.m_maxNum;
         }
         var _loc3_:int = this.m_currentStarNum / 10;
         var _loc4_:int = this.m_maxNum / 10;
         if(_loc3_ <= _loc4_)
         {
            if(_loc3_ > _loc2_)
            {
               this.m_isAdvanceNum10 = true;
            }
         }
      }
      
      public function UpdateStars(param1:Event) : *
      {
         var _loc9_:Number = NaN;
         var _loc10_:Number = NaN;
         var _loc11_:MovieClip = null;
         var _loc2_:int = this.m_currentStarNum / 10;
         var _loc3_:int = this.m_currentStarNum % 10;
         var _loc4_:int = this.m_maxNum / 10;
         var _loc5_:int = this.m_maxNum % 10;
         var _loc6_:int = this.m_sfOpenNum / 10;
         var _loc7_:int = this.m_sfOpenNum % 10;
         var _loc8_:int = 0;
         if(this.m_isAdvanceNum10)
         {
            _loc8_ = 0;
            while(_loc8_ < this.m_starSAnm.length)
            {
               if(Boolean(this.m_starSAnm[_loc8_]) && this.m_starSAnm[_loc8_].currentLabel == "off")
               {
                  if(_loc8_ > 0)
                  {
                     if(this.m_starSAnm[_loc8_ - 1])
                     {
                        if(this.m_starSAnm[_loc8_ - 1].currentLabel == "next" || this.m_starSAnm[_loc8_ - 1].currentLabel == "on")
                        {
                           this.m_starSAnm[_loc8_].gotoAndPlay("on_in");
                        }
                     }
                  }
                  else
                  {
                     this.m_starSAnm[_loc8_].gotoAndPlay("on_in");
                  }
               }
               _loc8_++;
            }
            if(Boolean(this.m_starSAnm[this.CCD_STARS_S_MAX - 1]) && this.m_starSAnm[this.CCD_STARS_S_MAX - 1].currentLabel == "on")
            {
               _loc8_ = 0;
               while(_loc8_ < this.m_starSAnm.length)
               {
                  if(this.m_starSAnm[_loc8_])
                  {
                     this.m_starSAnm[_loc8_].gotoAndStop("off");
                  }
                  _loc8_++;
               }
               _loc8_ = 0;
               while(_loc8_ < _loc2_)
               {
                  if(Boolean(this.m_starLAnm[_loc8_]) && this.m_starLAnm[_loc8_].currentLabel == "off")
                  {
                     this.m_starLAnm[_loc8_].gotoAndPlay("on_in");
                  }
                  _loc8_++;
               }
               if(_loc2_ >= _loc4_)
               {
                  _loc9_ = this.m_interval_s * 0.5;
                  _loc10_ = this.m_basePosX_s + _loc9_ * (10 - _loc5_);
                  _loc8_ = 0;
                  while(_loc8_ < this.m_starsS.length)
                  {
                     if(_loc8_ < _loc5_)
                     {
                        this.m_starsS[_loc8_].visible = true;
                     }
                     else
                     {
                        this.m_starsS[_loc8_].visible = false;
                     }
                     this.m_starsS[_loc8_].x = _loc10_ + this.m_interval_s * _loc8_;
                     _loc8_++;
                  }
               }
               _loc8_ = 0;
               while(_loc8_ < this.m_starsS.length)
               {
                  _loc11_ = MovieClip(this.m_starSAnm[_loc8_]["mc_mark"]);
                  if(_loc11_)
                  {
                     if(_loc2_ == _loc6_)
                     {
                        if(_loc8_ < _loc7_)
                        {
                           _loc11_.visible = true;
                        }
                        else
                        {
                           _loc11_.visible = false;
                        }
                     }
                     else if(_loc2_ > _loc6_)
                     {
                        _loc11_.visible = false;
                     }
                     else if(_loc2_ < _loc6_)
                     {
                        _loc11_.visible = true;
                     }
                  }
                  _loc8_++;
               }
               this.m_isAdvanceNum10 = false;
            }
         }
         else
         {
            _loc8_ = 0;
            while(_loc8_ < _loc3_)
            {
               if(Boolean(this.m_starSAnm[_loc8_]) && this.m_starSAnm[_loc8_].currentLabel == "off")
               {
                  if(_loc8_ > 0)
                  {
                     if(this.m_starSAnm[_loc8_ - 1])
                     {
                        if(this.m_starSAnm[_loc8_ - 1].currentLabel == "next" || this.m_starSAnm[_loc8_ - 1].currentLabel == "on")
                        {
                           this.m_starSAnm[_loc8_].gotoAndPlay("on_in");
                        }
                     }
                  }
                  else
                  {
                     this.m_starSAnm[_loc8_].gotoAndPlay("on_in");
                  }
               }
               _loc8_++;
            }
         }
         if(this.m_currentStarNum >= this.m_sfOpenNum)
         {
            _loc8_ = 0;
            while(_loc8_ < this.m_starsL.length)
            {
               if(this.m_starsL[_loc8_].currentLabel == "loop")
               {
                  this.m_starsL[_loc8_].gotoAndPlay("sf_ok");
               }
               _loc8_++;
            }
            _loc8_ = 0;
            while(_loc8_ < this.m_starsS.length)
            {
               if(this.m_starsS[_loc8_].currentLabel == "loop")
               {
                  this.m_starsS[_loc8_].gotoAndPlay("sf_ok");
               }
               _loc8_++;
            }
         }
      }
      
      public function SetStarsNumDirect(param1:int) : *
      {
         var _loc9_:MovieClip = null;
         this.m_currentStarNum = param1;
         if(this.m_currentStarNum > this.m_maxNum)
         {
            this.m_currentStarNum = this.m_maxNum;
         }
         var _loc2_:int = this.m_currentStarNum / 10;
         var _loc3_:int = this.m_currentStarNum % 10;
         var _loc4_:int = this.m_maxNum / 10;
         var _loc5_:int = this.m_maxNum % 10;
         var _loc6_:int = this.m_sfOpenNum / 10;
         var _loc7_:int = this.m_sfOpenNum % 10;
         var _loc8_:int = 0;
         _loc8_ = 0;
         while(_loc8_ < _loc2_)
         {
            if(_loc8_ < _loc2_)
            {
               this.m_starLAnm[_loc8_].gotoAndStop("on");
            }
            else
            {
               this.m_starLAnm[_loc8_].gotoAndStop("off");
            }
            _loc8_++;
         }
         _loc8_ = 0;
         while(_loc8_ < this.m_starSAnm.length)
         {
            if(_loc8_ < _loc3_)
            {
               this.m_starSAnm[_loc8_].gotoAndStop("on");
            }
            else
            {
               this.m_starSAnm[_loc8_].gotoAndStop("off");
            }
            _loc8_++;
         }
         if(_loc2_ >= _loc4_)
         {
            _loc8_ = 0;
            while(_loc8_ < this.m_starsS.length)
            {
               if(_loc8_ >= _loc5_)
               {
                  this.m_starsS[_loc8_].visible = false;
               }
               _loc8_++;
            }
         }
         _loc8_ = 0;
         while(_loc8_ < this.m_starsS.length)
         {
            _loc9_ = MovieClip(this.m_starSAnm[_loc8_]["mc_mark"]);
            if(_loc9_)
            {
               if(_loc2_ == _loc6_)
               {
                  if(_loc8_ < _loc7_)
                  {
                     _loc9_.visible = true;
                  }
                  else
                  {
                     _loc9_.visible = false;
                  }
               }
               else if(_loc2_ > _loc6_)
               {
                  _loc9_.visible = false;
               }
               else if(_loc2_ < _loc6_)
               {
                  _loc9_.visible = true;
               }
            }
            _loc8_++;
         }
      }
   }
}

