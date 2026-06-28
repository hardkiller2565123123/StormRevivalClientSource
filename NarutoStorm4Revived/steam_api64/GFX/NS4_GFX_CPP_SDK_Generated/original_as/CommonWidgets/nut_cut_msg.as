package script.cutin_msg
{
   import flash.display.MovieClip;
   import flash.events.Event;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public class nut_cut_msg extends MovieClip
   {
      
      public var mc_bg:smb_cut_bg;
      
      public var mc_msg:MovieClip;
      
      private const LOOP_TIME:* = 30;
      
      private const CCD_MULTIPLE_LINE_HEIGHT_RATE:Number = 1.25;
      
      private const CCD_MULTIPLE_LINE_WIDTH:Number = 1650;
      
      private var m_isActive:Boolean;
      
      private var m_loopTime:int;
      
      public function nut_cut_msg()
      {
         super();
         addFrameScript(34,this.frame35,44,this.frame45);
         this.visible = false;
         this.m_isActive = false;
         this.m_loopTime = 0;
      }
      
      public function Play(param1:String) : *
      {
         var _loc3_:smb_font = null;
         this.gotoAndPlay("in");
         var _loc2_:MovieClip = MovieClip(this["mc_msg"]);
         if(_loc2_)
         {
            _loc3_ = smb_font(_loc2_["txt_msg"]);
            if(_loc3_)
            {
               _loc3_.SetText(param1);
            }
         }
         this.visible = true;
         this.m_isActive = true;
         this.m_loopTime = this.LOOP_TIME;
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         if(this.currentLabel == "loop")
         {
            if(--this.m_loopTime <= 0)
            {
               this.gotoAndPlay("out");
            }
         }
         else if(this.currentFrame == this.totalFrames)
         {
            this.visible = false;
            this.m_isActive = false;
            removeEventListener(Event.ENTER_FRAME,this.Update);
         }
      }
      
      public function IsEnd() : Boolean
      {
         return !this.m_isActive;
      }
      
      public function SetEnableMultipleLine() : *
      {
         this["mc_bg"]["mc_bg"].height = this.CCD_MULTIPLE_LINE_HEIGHT_RATE * this["mc_bg"]["mc_bg"].height;
         var _loc1_:smb_font = smb_font(this["mc_msg"]["txt_msg"]);
         _loc1_.SetTextFieldWidth(this.CCD_MULTIPLE_LINE_WIDTH);
         _loc1_.SetTextWordWrap(true);
      }
      
      internal function frame35() : *
      {
         this.stop();
      }
      
      internal function frame45() : *
      {
         this.stop();
      }
   }
}

