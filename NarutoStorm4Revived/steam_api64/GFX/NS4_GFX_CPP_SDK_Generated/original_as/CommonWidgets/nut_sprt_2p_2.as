package script.gauge_sprt
{
   import ELoader.ExtendLoader;
   import flash.display.DisplayObject;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.gauge_plat.nut_btn;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol17")]
   public class nut_sprt_2p extends MovieClip
   {
      
      public static const CCD_MEMBER_NUM:int = 3;
      
      public var dmy_char2:nut_tex00;
      
      public var mc_sp_eff_1:MovieClip;
      
      public var dmy_char1:nut_tex00;
      
      public var mc_sp_eff_2:MovieClip;
      
      public var mc_gauge2:MovieClip;
      
      public var mc_gauge1:MovieClip;
      
      public var mc_btn1:nut_btn;
      
      public var mc_btn2:nut_btn;
      
      public var GetFaceIconName:Function;
      
      public var GetAwakeIconName:Function;
      
      public var GetSupportLKeyName:Function;
      
      public var GetSupportRKeyName:Function;
      
      public var IsAwakeSupportL:Function;
      
      public var IsAwakeSupportR:Function;
      
      private var m_loaderL:Array = new Array(3);
      
      private var m_loaderR:Array = new Array(3);
      
      private var m_loaderAwakeL:Array = new Array(3);
      
      private var m_loaderAwakeR:Array = new Array(3);
      
      private var m_memberNum:int;
      
      private var m_gaugeRateL:Number;
      
      private var m_gaugeRateR:Number;
      
      private var m_fadeFrame:int;
      
      private var m_fadeRate:Number;
      
      private var m_side:int = 1;
      
      public function nut_sprt_2p()
      {
         super();
         addFrameScript(0,this.frame1,9,this.frame10,18,this.frame19,28,this.frame29,39,this.frame40,50,this.frame51,51,this.frame52,62,this.frame63,71,this.frame72,80,this.frame81,89,this.frame90);
         this.mc_sp_eff_1.visible = false;
         this.mc_sp_eff_1.stop();
         this.mc_sp_eff_2.visible = false;
         this.mc_sp_eff_2.stop();
         this.mc_gauge1.visible = false;
         this.mc_gauge1.stop();
         this.mc_gauge2.visible = false;
         this.mc_gauge2.stop();
         var _loc1_:int = 0;
         while(_loc1_ < CCD_MEMBER_NUM)
         {
            this.m_loaderL[_loc1_] = new ExtendLoader();
            this.m_loaderR[_loc1_] = new ExtendLoader();
            this.m_loaderAwakeL[_loc1_] = new ExtendLoader();
            this.m_loaderAwakeR[_loc1_] = new ExtendLoader();
            _loc1_++;
         }
      }
      
      public function Initialize(param1:int) : *
      {
         this.m_gaugeRateL = 1;
         this.m_gaugeRateR = 1;
         this.m_fadeFrame = 0;
         this.m_fadeRate = 0;
         this.m_memberNum = param1;
         if(this.m_memberNum == 1)
         {
            this.visible = false;
            this.stop();
            return;
         }
         if(this.m_memberNum == 2)
         {
            this.gotoAndStop("2cell_loop");
         }
         else if(this.m_memberNum == 3)
         {
            this.gotoAndStop("3cell_loop");
         }
         this.LoadIcon();
         this.SetFaceIconL(1);
         this.SetFaceIconR(2);
         var _loc2_:String = this.GetSupportLKeyName(this.m_side);
         trace("Sprt2P_InitL:" + _loc2_);
         this.mc_btn2.gotoAndStop(_loc2_);
         _loc2_ = this.GetSupportRKeyName(this.m_side);
         this.mc_btn1.gotoAndStop(_loc2_);
         trace("Sprt2P_InitR:" + _loc2_);
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         var _loc1_:int = 0;
         while(_loc1_ < CCD_MEMBER_NUM)
         {
            this.m_loaderL[_loc1_].unload();
            this.m_loaderR[_loc1_].unload();
            this.m_loaderAwakeL[_loc1_].unload();
            this.m_loaderAwakeR[_loc1_].unload();
            _loc1_++;
         }
         removeEventListener(Event.ENTER_FRAME,this.Update);
         removeEventListener(Event.ENTER_FRAME,this.UpdateOutAnm);
      }
      
      public function Update(param1:Event) : *
      {
         var _loc2_:int = 0;
         var _loc3_:int = 0;
         var _loc4_:int = 0;
         var _loc5_:int = 0;
         var _loc6_:int = 0;
         var _loc7_:int = 0;
         if(this.m_memberNum == 2)
         {
            _loc2_ = this.mc_gauge1.totalFrames;
            _loc3_ = this.m_gaugeRateL * _loc2_;
            this.mc_gauge1.gotoAndStop(_loc3_);
            if(this.mc_gauge1.currentLabel == "max")
            {
               if(this.mc_gauge1.visible == true)
               {
                  this.mc_gauge1.visible = false;
                  this.mc_sp_eff_1.visible = true;
                  this.mc_sp_eff_1.gotoAndPlay(1);
               }
            }
            else if(this.mc_gauge1.visible == false)
            {
               this.mc_gauge1.visible = true;
               this.mc_sp_eff_1.visible = true;
               this.mc_sp_eff_1.gotoAndPlay(1);
            }
         }
         else if(this.m_memberNum == 3)
         {
            _loc4_ = this.mc_gauge2.totalFrames;
            _loc5_ = this.m_gaugeRateL * _loc4_;
            this.mc_gauge2.gotoAndStop(_loc5_);
            if(this.mc_gauge2.currentLabel == "max")
            {
               if(this.mc_gauge2.visible == true)
               {
                  this.mc_gauge2.visible = false;
                  this.mc_sp_eff_2.visible = true;
                  this.mc_sp_eff_2.gotoAndPlay(1);
               }
            }
            else if(this.mc_gauge2.visible == false)
            {
               this.mc_gauge2.visible = true;
               this.mc_sp_eff_2.visible = true;
               this.mc_sp_eff_2.gotoAndPlay(1);
            }
            _loc6_ = this.mc_gauge1.totalFrames;
            _loc7_ = this.m_gaugeRateR * _loc6_;
            this.mc_gauge1.gotoAndStop(_loc7_);
            if(this.mc_gauge1.currentLabel == "max")
            {
               if(this.mc_gauge1.visible == true)
               {
                  this.mc_gauge1.visible = false;
                  this.mc_sp_eff_1.visible = true;
                  this.mc_sp_eff_1.gotoAndPlay(1);
               }
            }
            else if(this.mc_gauge1.visible == false)
            {
               this.mc_gauge1.visible = true;
               this.mc_sp_eff_1.visible = true;
               this.mc_sp_eff_1.gotoAndPlay(1);
            }
         }
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         this.visible = param1;
      }
      
      public function SetGaugeRateL(param1:Number) : *
      {
         this.m_gaugeRateL = param1;
      }
      
      public function SetGaugeRateR(param1:Number) : *
      {
         this.m_gaugeRateR = param1;
      }
      
      public function LoadIcon() : *
      {
         var faceIconName:String = null;
         var awakeIconName:String = null;
         var faceUrl:URLRequest = null;
         var awakeUrl:URLRequest = null;
         var memberIdx:int = 0;
         while(memberIdx < CCD_MEMBER_NUM)
         {
            faceIconName = String(this.GetFaceIconName(this.m_side,memberIdx));
            if(faceIconName != "")
            {
               faceUrl = new URLRequest("../charicon_sprt/sprt_" + faceIconName + ".xfbin");
               this.m_loaderL[memberIdx].load(faceUrl);
               this.m_loaderL[memberIdx].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
               if(this.m_memberNum == 3)
               {
                  this.m_loaderR[memberIdx].load(faceUrl);
                  this.m_loaderR[memberIdx].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
               }
            }
            awakeIconName = String(this.GetAwakeIconName(this.m_side,memberIdx));
            if(awakeIconName != "")
            {
               awakeUrl = new URLRequest("../charicon_sprt/sprt_" + awakeIconName + ".xfbin");
               this.m_loaderAwakeL[memberIdx].load(awakeUrl);
               this.m_loaderAwakeL[memberIdx].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
               if(this.m_memberNum == 3)
               {
                  this.m_loaderAwakeR[memberIdx].load(awakeUrl);
                  this.m_loaderAwakeR[memberIdx].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
               }
            }
            memberIdx++;
         }
         this.m_loaderL[this.m_memberNum - 1].contentLoaderInfo.addEventListener(Event.COMPLETE,function(param1:Event):void
         {
            var _loc2_:int = 0;
            while(_loc2_ < m_memberNum)
            {
               if(m_memberNum == 2)
               {
                  dmy_char1.addChild(m_loaderL[_loc2_]);
               }
               else if(m_memberNum == 3)
               {
                  dmy_char1.addChild(m_loaderR[_loc2_]);
                  dmy_char2.addChild(m_loaderL[_loc2_]);
               }
               _loc2_++;
            }
         });
         this.m_loaderAwakeL[this.m_memberNum - 1].contentLoaderInfo.addEventListener(Event.COMPLETE,function(param1:Event):void
         {
            var _loc2_:int = 0;
            while(_loc2_ < m_memberNum)
            {
               if(m_memberNum == 2)
               {
                  dmy_char1.addChild(m_loaderAwakeL[_loc2_]);
               }
               else if(m_memberNum == 3)
               {
                  dmy_char1.addChild(m_loaderAwakeR[_loc2_]);
                  dmy_char2.addChild(m_loaderAwakeL[_loc2_]);
               }
               _loc2_++;
            }
         });
      }
      
      public function SetFaceIconL(param1:int) : *
      {
         var _loc2_:int = 0;
         while(_loc2_ < this.m_memberNum)
         {
            DisplayObject(this.m_loaderL[_loc2_]).visible = false;
            DisplayObject(this.m_loaderAwakeL[_loc2_]).visible = false;
            _loc2_++;
         }
         if(this.IsAwakeSupportL(this.m_side))
         {
            DisplayObject(this.m_loaderAwakeL[param1]).visible = true;
         }
         else
         {
            DisplayObject(this.m_loaderL[param1]).visible = true;
         }
      }
      
      public function SetFaceIconR(param1:int) : *
      {
         var _loc2_:int = 0;
         if(this.m_memberNum == 3)
         {
            _loc2_ = 0;
            while(_loc2_ < this.m_memberNum)
            {
               DisplayObject(this.m_loaderR[_loc2_]).visible = false;
               DisplayObject(this.m_loaderAwakeR[_loc2_]).visible = false;
               _loc2_++;
            }
            if(this.IsAwakeSupportR(this.m_side))
            {
               DisplayObject(this.m_loaderAwakeR[param1]).visible = true;
            }
            else
            {
               DisplayObject(this.m_loaderR[param1]).visible = true;
            }
         }
      }
      
      public function ResetGaugeInputPad() : *
      {
         var _loc1_:String = this.GetSupportLKeyName(this.m_side);
         this.mc_btn2.gotoAndStop(_loc1_);
         _loc1_ = this.GetSupportRKeyName(this.m_side);
         this.mc_btn1.gotoAndStop(_loc1_);
      }
      
      public function PlayOutAnm(param1:int) : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
         this.m_fadeFrame = param1;
         if(this.m_fadeFrame == 0)
         {
            this.m_fadeRate = -1;
         }
         else
         {
            this.m_fadeRate = -(1 / this.m_fadeFrame);
         }
         addEventListener(Event.ENTER_FRAME,this.UpdateOutAnm);
      }
      
      public function UpdateOutAnm(param1:Event) : *
      {
         if(this.m_fadeFrame >= 0)
         {
            --this.m_fadeFrame;
            this.alpha += this.m_fadeRate;
            if(this.alpha < 0)
            {
               this.alpha = 0;
            }
            else if(this.alpha > 1)
            {
               this.alpha = 1;
            }
         }
         else
         {
            removeEventListener(Event.ENTER_FRAME,this.UpdateOutAnm);
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame10() : *
      {
         this.gotoAndStop("3cell_loop");
      }
      
      internal function frame19() : *
      {
         this.gotoAndStop("3cell_loop");
      }
      
      internal function frame29() : *
      {
         this.gotoAndStop("3cell_loop");
      }
      
      internal function frame40() : *
      {
         this.gotoAndStop("3cell_loop");
      }
      
      internal function frame51() : *
      {
         this.gotoAndStop("3cell_loop");
      }
      
      internal function frame52() : *
      {
         this.stop();
      }
      
      internal function frame63() : *
      {
         this.gotoAndStop("2cell_loop");
      }
      
      internal function frame72() : *
      {
         this.gotoAndStop("2cell_loop");
      }
      
      internal function frame81() : *
      {
         this.gotoAndStop("2cell_loop");
      }
      
      internal function frame90() : *
      {
         this.gotoAndStop("2cell_loop");
      }
   }
}

