package script.gauge_last
{
   import ELoader.ExtendLoader;
   import flash.display.DisplayObject;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.gauge_cmn.*;
   import script.gauge_plat.nut_btn;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol28")]
   public class nut_gauge_1p extends MovieClip
   {
      
      public var all_eff_awk:anm_eff_ckr;
      
      public var all_gauge_btn:nut_btn;
      
      public var all_ckr:MovieClip;
      
      public var all_bg_eff:nut_main_bg1;
      
      public var all_bg2:MovieClip;
      
      public var all_life:MovieClip;
      
      public var dmy_char:nut_tex00;
      
      public var all_bg:nut_main_bg1;
      
      public var dmy_name:nut_tex00;
      
      public var all_eff_ckr:anm_eff_ckr;
      
      public var all_kwrm:MovieClip;
      
      private const ONE_GAUGE_VOLUME:* = 0.5;
      
      public var GetDodgeKeyName:Function;
      
      public var SetWaving:Function;
      
      private var m_loaderFace:Array = new Array(GaugeLastParam.CCD_FACE_ICON_SET_NUM);
      
      private var m_loaderName:ExtendLoader = new ExtendLoader();
      
      private var m_effChakra:MovieClip;
      
      private var m_effAwake:MovieClip;
      
      private var m_allBg:MovieClip;
      
      private var m_allBg2:MovieClip;
      
      private var m_isLoopShiftEff:Boolean;
      
      private var m_isBreakLifeGauge:Boolean;
      
      private var m_side:int = 0;
      
      public function nut_gauge_1p()
      {
         super();
         addFrameScript(0,this.frame1,6,this.frame7,34,this.frame35);
         var _loc1_:int = 0;
         while(_loc1_ < GaugeLastParam.CCD_FACE_ICON_SET_NUM)
         {
            this.m_loaderFace[_loc1_] = new ExtendLoader();
            _loc1_++;
         }
      }
      
      public function Initialize() : *
      {
         this.m_effChakra = MovieClip(getChildByName("all_eff_ckr"));
         this.SetChakraCharge(false);
         this.m_effAwake = MovieClip(getChildByName("all_eff_awk"));
         this.SetAwakeEffect(false);
         this.m_allBg = MovieClip(getChildByName("all_bg"));
         this.m_allBg2 = MovieClip(getChildByName("all_bg2"));
         if(this.m_allBg2)
         {
            this.m_allBg2.visible = false;
         }
         this.m_isLoopShiftEff = false;
         this.m_isBreakLifeGauge = false;
         this.all_gauge_btn.gotoAndStop(this.GetDodgeKeyName(this.m_side));
         this.LoadIcon();
         this.SetFaceIcon(0);
         this.SetNameIcon(0);
      }
      
      public function Finalize() : *
      {
         var _loc1_:int = 0;
         while(_loc1_ < GaugeLastParam.CCD_FACE_ICON_SET_NUM)
         {
            this.m_loaderFace[_loc1_].unload();
            _loc1_++;
         }
         this.m_loaderName.unload();
         removeEventListener(Event.ENTER_FRAME,this.ProcWaveEffect);
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         this.visible = param1;
      }
      
      public function SetEnableChakraGauge(param1:Boolean) : *
      {
      }
      
      public function SetChakraCharge(param1:Boolean) : *
      {
         if(this.m_effChakra)
         {
            this.m_effChakra.visible = param1;
         }
      }
      
      private function ProcWaveEffect(param1:Event) : *
      {
         if(this.m_isLoopShiftEff == false)
         {
            if(this.currentFrame == this.totalFrames - 1)
            {
               this.gotoAndStop("loop");
               this.SetWaving(false);
               removeEventListener(Event.ENTER_FRAME,this.ProcWaveEffect);
            }
         }
      }
      
      public function RequestStartWaveEffect() : *
      {
         this.gotoAndPlay("shift");
         this.SetWaving(true);
         addEventListener(Event.ENTER_FRAME,this.ProcWaveEffect);
      }
      
      public function SetLoopWaveEffect(param1:Boolean) : *
      {
         this.m_isLoopShiftEff = param1;
      }
      
      public function SetAwakeEffect(param1:Boolean) : *
      {
         if(this.m_effAwake)
         {
            this.m_effAwake.visible = param1;
         }
         var _loc2_:nut_ckr = nut_ckr(getChildByName("all_ckr.mc_ckr"));
         if(_loc2_)
         {
            _loc2_.SetSpAtkVisible(!param1);
         }
      }
      
      public function SetEnableKawarimiGauge(param1:Boolean) : *
      {
         this.all_kwrm.visible = param1;
         this.all_gauge_btn.visible = param1;
      }
      
      public function LoadIcon() : *
      {
         var nameIconName:String;
         var i:int = 0;
         var faceIconName:String = null;
         var faceUrl:URLRequest = null;
         var nameUrl:URLRequest = null;
         i = 0;
         i = 0;
         while(i < GaugeLastParam.CCD_FACE_ICON_SET_NUM)
         {
            faceIconName = String(GaugeLastParam.CCD_FACE_ICON_TBL[this.m_side][i]);
            if(faceIconName == "")
            {
               faceIconName = "xxx1";
            }
            if(faceIconName != "")
            {
               faceUrl = new URLRequest("../charicon_p/p_" + faceIconName + ".xfbin");
               this.m_loaderFace[i].load(faceUrl);
               this.m_loaderFace[i].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            }
            i++;
         }
         nameIconName = String(GaugeLastParam.CCD_NAME_ICON_TBL[this.m_side]);
         if(nameIconName == "")
         {
            nameIconName = "xxx1";
         }
         if(nameIconName != "")
         {
            nameUrl = new URLRequest("../name_m/LANG/nm_" + nameIconName + ".xfbin");
            this.m_loaderName.load(nameUrl);
            this.m_loaderName.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_LEFT);
         }
         this.m_loaderFace[GaugeLastParam.CCD_FACE_ICON_SET_NUM - 1].contentLoaderInfo.addEventListener(Event.COMPLETE,function(param1:Event):void
         {
            i = 0;
            while(i < GaugeLastParam.CCD_FACE_ICON_SET_NUM)
            {
               dmy_char.addChild(m_loaderFace[i]);
               ++i;
            }
         });
         this.m_loaderName.contentLoaderInfo.addEventListener(Event.COMPLETE,function(param1:Event):void
         {
            dmy_name.addChild(m_loaderName);
         });
      }
      
      public function SetFaceIcon(param1:int) : *
      {
         var _loc2_:int = 0;
         while(_loc2_ < GaugeLastParam.CCD_FACE_ICON_SET_NUM)
         {
            DisplayObject(this.m_loaderFace[_loc2_]).visible = false;
            _loc2_++;
         }
         DisplayObject(this.m_loaderFace[param1]).visible = true;
      }
      
      public function SetNameIcon(param1:int) : *
      {
         DisplayObject(this.m_loaderName).visible = true;
      }
      
      public function SetLifeRate(param1:Number) : *
      {
         var _loc2_:Number = NaN;
         var _loc3_:MovieClip = null;
         var _loc4_:int = 0;
         if(param1 < this.ONE_GAUGE_VOLUME)
         {
            _loc2_ = param1 * 2;
            if(this.m_isBreakLifeGauge)
            {
               _loc3_ = MovieClip(getChildByName("all_life"));
               if(_loc3_)
               {
                  _loc4_ = _loc3_.totalFrames * (1 - _loc2_);
                  _loc3_.gotoAndStop(_loc4_);
                  if(this.currentLabel == "loop" && _loc4_ > 15)
                  {
                     this.gotoAndPlay("break");
                  }
               }
            }
         }
      }
      
      public function BreakLifeGauge() : *
      {
         this.m_isBreakLifeGauge = true;
      }
      
      public function BreakChakraGauge(param1:Boolean) : *
      {
         if(this.m_allBg2)
         {
            this.m_allBg2.visible = true;
         }
         this.gotoAndPlay("break");
         var _loc2_:MovieClip = MovieClip(getChildByName("all_ckr"));
         if(_loc2_)
         {
            if(param1)
            {
               _loc2_.gotoAndPlay("half");
            }
            else
            {
               _loc2_.gotoAndPlay("emp");
            }
         }
      }
      
      public function BreakDodgeGauge() : *
      {
         this.gotoAndPlay("break");
         var _loc1_:MovieClip = MovieClip(getChildByName("all_gauge_btn"));
         if(_loc1_)
         {
            _loc1_.visible = false;
         }
         var _loc2_:MovieClip = MovieClip(getChildByName("all_kwrm"));
         if(_loc2_)
         {
            _loc2_.gotoAndPlay("break");
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame7() : *
      {
         this.gotoAndStop("loop");
      }
      
      internal function frame35() : *
      {
         gotoAndPlay("shift");
      }
   }
}

