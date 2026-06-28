package script.msg_match_m_txt
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol22")]
   public class nut_msg_match_num extends MovieClip
   {
      
      public var mc_num1:MovieClip;
      
      public var mc_num10:MovieClip;
      
      public var mc_num100:MovieClip;
      
      public function nut_msg_match_num()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         stop();
      }
   }
}

