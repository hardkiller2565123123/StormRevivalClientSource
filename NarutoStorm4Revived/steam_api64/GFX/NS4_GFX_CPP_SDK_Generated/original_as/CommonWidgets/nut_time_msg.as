package script.num_time
{
   import flash.display.MovieClip;
   import flash.external.*;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public class nut_time_msg extends MovieClip
   {
      
      public var mc_msg:MovieClip;
      
      public function nut_time_msg()
      {
         super();
         addFrameScript(44,this.frame45,84,this.frame85);
      }
      
      public function SetWarning() : *
      {
         gotoAndPlay("in");
         var _loc1_:MovieClip = MovieClip(this.getChildByName("mc_msg"));
         _loc1_ = MovieClip(_loc1_.getChildByName("txt_msg"));
         _loc1_.SetText(String(ExternalInterface.call("MessageConvert","boss_help_001")));
      }
      
      public function EraceWarning() : *
      {
         gotoAndPlay("out");
      }
      
      internal function frame45() : *
      {
         gotoAndPlay("loop");
      }
      
      internal function frame85() : *
      {
         this.stop();
      }
   }
}

