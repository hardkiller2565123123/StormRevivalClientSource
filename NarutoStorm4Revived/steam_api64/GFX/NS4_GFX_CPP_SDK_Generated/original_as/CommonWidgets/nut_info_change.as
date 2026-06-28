package script.info_wrong1
{
   import flash.display.MovieClip;
   import script.info_wrong1_lang.smb_wrong1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class nut_info_change extends MovieClip
   {
      
      public var mc_msg1:smb_wrong1;
      
      public function nut_info_change()
      {
         super();
         addFrameScript(35,this.frame36,54,this.frame55);
         stop();
      }
      
      public function IsLoopAnmNow() : Boolean
      {
         var _loc1_:Boolean = false;
         if(currentFrameLabel == "loop")
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      public function IsOutAnmEnd() : Boolean
      {
         var _loc1_:Boolean = false;
         if(currentFrameLabel == "end")
         {
            _loc1_ = true;
         }
         return _loc1_;
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         visible = param1;
      }
      
      public function SetAlpha(param1:Number) : *
      {
         this.alpha = param1;
      }
      
      internal function frame36() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame55() : *
      {
         this.stop();
      }
   }
}

