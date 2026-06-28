package script.stagesel
{
   import ELoader.ExtendLoader;
   import Enum.Enum;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   import script.icon_confirm.nut_conf_l;
   import script.num_time.nut_time;
   import script.stagesel_txt.nut_title_txt;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol24")]
   public class nut_stagesel extends MovieClip
   {
      
      public var all_bg_base:nut_bg_base;
      
      public var all_conf_l:nut_conf_l;
      
      public var all_count:nut_time;
      
      public var all_stage_image:nut_stage_image;
      
      public var all_stagetitle:nut_title;
      
      public var all_title_txt:nut_title_txt;
      
      public var mc_caution:MovieClip;
      
      public var StartFadeOut:Function;
      
      public var IsEndFade:Function;
      
      public var SetEnd:Function;
      
      private const CCD_LOADER_01:*;
      
      private const CCD_LOADER_02:*;
      
      private const CCD_LOADER_NUM:*;
      
      private const CCD_STAGE_NUM:int = 40;
      
      private const CCD_GAME_FPS:* = 30;
      
      private var m_waitCount:Number;
      
      private var m_stageName:smb_font;
      
      private var m_conf:MovieClip = null;
      
      private var m_caution:MovieClip = null;
      
      private var m_stageImg:nut_stage_image = null;
      
      private var m_timer:nut_time = null;
      
      private var m_bgDummy:MovieClip = null;
      
      private var m_loader:Array;
      
      private var m_timeCounter:int;
      
      private var m_fpsCounter:int;
      
      private var m_currentStage:int;
      
      private var m_fadeWaitCount:int;
      
      private var m_updateStep:int;
      
      private var m_bgUrl:URLRequest;
      
      public function nut_stagesel()
      {
         var _loc2_:URLRequest = null;
         this.CCD_LOADER_01 = Enum.Next(0);
         this.CCD_LOADER_02 = Enum.Next();
         this.CCD_LOADER_NUM = Enum.Next();
         this.m_loader = new Array(this.CCD_LOADER_NUM);
         super();
         addFrameScript(6,this.frame7,12,this.frame13);
         this.m_conf = this["all_conf_l"];
         if(this.m_conf)
         {
            this.m_conf.visible = false;
         }
         this.m_conf.stop();
         this.m_caution = this["mc_caution"];
         if(this.m_caution)
         {
            this.m_caution.visible = false;
         }
         this.m_stageName = smb_font(this.all_stagetitle["txt_stagetitle"]);
         if(this.m_stageName)
         {
            this.m_stageName.SetTextPivot(smb_font.CCD_PIVOT_CC);
         }
         this.m_stageImg = this["all_stage_image"];
         this.m_timer = this["all_count"];
         if(this.m_timer)
         {
            this.m_timer.visible = false;
         }
         this.m_bgDummy = this["all_bg_base"]["dmy_backgraund"];
         var _loc1_:int = 0;
         while(_loc1_ < this.CCD_LOADER_NUM - 1)
         {
            this.m_loader[_loc1_] = new ExtendLoader();
            this.m_loader[_loc1_].SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            _loc2_ = new URLRequest("tex_l/st_img_l_00.xfbin");
            this.m_loader[_loc1_].load(_loc2_);
            this.m_bgDummy.addChild(this.m_loader[_loc1_]);
            this.m_bgDummy.alpha = 0;
            _loc1_++;
         }
         this.m_timeCounter = 0;
         this.m_fpsCounter = 0;
         this.m_currentStage = 0;
         this.m_fadeWaitCount = 0;
         this.m_updateStep = -1;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         var _loc2_:String = null;
         switch(this.m_updateStep)
         {
            case 0:
               if(this.m_fadeWaitCount > 0)
               {
                  --this.m_fadeWaitCount;
                  if(this.m_fadeWaitCount == 0)
                  {
                     ++this.m_updateStep;
                  }
               }
               break;
            case 1:
               _loc2_ = "";
               if(this.m_currentStage < 10)
               {
                  _loc2_ += "0";
               }
               _loc2_ += this.m_currentStage.toString();
               this.m_bgUrl = new URLRequest("tex_l/st_img_l_" + _loc2_ + ".xfbin");
               this.m_loader[this.CCD_LOADER_01].load(this.m_bgUrl);
               ++this.m_updateStep;
               break;
            case 2:
               if(this.m_loader[this.CCD_LOADER_01].IsLoadedAll() == true)
               {
                  this.m_bgDummy.alpha = 0;
                  ++this.m_updateStep;
               }
               break;
            case 3:
               if(this.m_bgDummy.alpha < 1)
               {
                  this.m_bgDummy.alpha += 0.2;
               }
               trace("m_bgDummy.alpha : " + this.m_bgDummy.alpha);
               if(this.m_bgDummy.alpha >= 1)
               {
                  ++this.m_updateStep;
               }
         }
      }
      
      public function SetStageInfo(param1:int, param2:String, param3:String) : *
      {
         var _loc5_:smb_font = null;
         var _loc6_:MovieClip = null;
         this.m_stageName.SetText(param2);
         this.m_caution.visible = false;
         if(param3 != "")
         {
            this.m_caution.visible = true;
            _loc5_ = smb_font(this.m_caution["txt_caution"]);
            if(_loc5_)
            {
               _loc5_.SetText(param3);
            }
            _loc6_ = MovieClip(this.m_caution["mc_caution_b"]);
            if(_loc6_)
            {
               _loc6_.width = _loc5_.width + 100;
            }
         }
         this.m_currentStage = param1;
         this.m_updateStep = 0;
         var _loc4_:int = 8;
         this.m_fadeWaitCount = _loc4_;
      }
      
      public function Decide() : *
      {
         if(this.m_conf)
         {
            this.m_conf.visible = true;
            this.m_conf.gotoAndPlay(0);
         }
      }
      
      public function StartOut(param1:Number) : *
      {
         this.m_waitCount = param1;
         addEventListener(Event.ENTER_FRAME,this.UpdateWait);
      }
      
      public function UpdateWait(param1:Event) : *
      {
         if(--this.m_waitCount <= 0)
         {
            this.m_waitCount = 0;
            if(this.m_loader[this.CCD_LOADER_01].visible == true && this.m_loader[this.CCD_LOADER_01].alpha >= 1)
            {
               this.gotoAndPlay("out");
               this.StartFadeOut();
               removeEventListener(Event.ENTER_FRAME,this.UpdateWait);
               addEventListener(Event.ENTER_FRAME,this.UpdateOut);
            }
         }
      }
      
      public function UpdateOut(param1:Event) : *
      {
         if(this.currentFrame == this.totalFrames && this.IsEndFade() == true)
         {
            this.m_stageImg.PopKeyHelp();
            this.SetEnd();
            removeEventListener(Event.ENTER_FRAME,this.UpdateOut);
         }
      }
      
      public function SetTimer(param1:int) : *
      {
         this.m_timeCounter = param1;
         this.m_fpsCounter = this.CCD_GAME_FPS;
         this.m_timer.visible = true;
         this.m_timer.SetTimeCount(this.m_timeCounter);
         addEventListener(Event.ENTER_FRAME,this.UpdateTimer);
      }
      
      public function UpdateTimer(param1:Event) : *
      {
         if(--this.m_fpsCounter <= 0)
         {
            this.m_fpsCounter = this.CCD_GAME_FPS;
            if(--this.m_timeCounter <= 0)
            {
               this.m_timer.SetTimeCount(0);
               this.m_stageImg.TimeOver();
               removeEventListener(Event.ENTER_FRAME,this.UpdateTimer);
            }
            else
            {
               this.m_timer.SetTimeCount(this.m_timeCounter);
            }
         }
      }
      
      public function StopTimer() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.UpdateTimer);
      }
      
      public function SetInstallMode() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
         this.m_bgDummy.alpha = 1;
      }
      
      internal function frame7() : *
      {
         stop();
      }
      
      internal function frame13() : *
      {
         stop();
      }
   }
}

