package script.msg_wins_txt
{
   import flash.display.MovieClip;
   import script.num_l.nut_num_l;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol4")]
   public class nut_wins extends MovieClip
   {
      
      public var mc_msg1:MovieClip;
      
      public var mc_num1:nut_num_l;
      
      public var mc_num10:nut_num_l;
      
      public var mc_num100:nut_num_l;
      
      public function nut_wins()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame2() : *
      {
         this.stop();
      }
      
      internal function frame3() : *
      {
         this.stop();
      }
   }
}

