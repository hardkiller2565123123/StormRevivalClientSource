package script.result_main
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol137")]
   public class nut_info_btl extends MovieClip
   {
      
      internal static const STEP_NONE:Number = 0;
      
      internal static const STEP_IN:Number = 1;
      
      internal static const STEP_IN_END:Number = 2;
      
      internal static const STEP_IDLE:Number = 3;
      
      internal static const STEP_CLOSE:Number = 4;
      
      internal static const STEP_CLOSE_END:Number = 5;
      
      internal static const STEP_END:Number = 6;
      
      internal static const STEP_NUM:Number = 7;
      
      public var mc_info:MovieClip;
      
      public var SetOpend:Function;
      
      public var SetClosed:Function;
      
      private var m_step:int;
      
      private var m_count:int;
      
      public function nut_info_btl()
      {
         super();
         addFrameScript(19,this.frame20,29,this.frame30);
         this.m_step = STEP_NONE;
         this.m_count = 0;
      }
      
      public function Initialize() : *
      {
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
         this.mc_info.txt_info.SetText(String(ExternalInterface.call("MessageConvert","networkmode_107")));
         gotoAndStop("in");
         this.m_count = 0;
      }
      
      public function onEnterFrameCtrl(param1:*) : void
      {
         switch(this.m_step)
         {
            case STEP_NONE:
               break;
            case STEP_IN:
               this.m_step = STEP_IN_END;
               break;
            case STEP_IN_END:
               if(currentFrameLabel == "loop")
               {
                  this.SetOpend(true);
                  this.m_step = STEP_IDLE;
                  this.m_count = 0;
               }
               break;
            case STEP_IDLE:
               break;
            case STEP_CLOSE:
               this.m_step = STEP_CLOSE_END;
               break;
            case STEP_CLOSE_END:
               if(currentFrame == totalFrames)
               {
                  this.SetClosed(true);
                  this.m_step = STEP_END;
               }
               break;
            case STEP_END:
         }
      }
      
      public function OpenBattleRematch() : *
      {
         this.m_step = STEP_IN;
         this.SetOpend(false);
         this.SetClosed(false);
         gotoAndPlay("in");
         ExternalInterface.call("RequestPlaySE",int(SeId.CCD_SE_ID_TUTORIAL));
      }
      
      public function CloseBattleRematch() : *
      {
         this.m_step = STEP_CLOSE;
         gotoAndPlay("out");
      }
      
      internal function frame20() : *
      {
         this.stop();
      }
      
      internal function frame30() : *
      {
         this.stop();
      }
   }
}

