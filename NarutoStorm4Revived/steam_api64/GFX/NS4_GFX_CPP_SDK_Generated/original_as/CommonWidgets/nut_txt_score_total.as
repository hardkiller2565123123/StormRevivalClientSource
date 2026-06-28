package script.freebtl_leag
{
   import flash.display.MovieClip;
   import script.num_l.nut_num_l;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class nut_txt_score_total extends MovieClip
   {
      
      public var mc_num_l_1:nut_num_l;
      
      public var mc_num_l_10:nut_num_l;
      
      public var mc_num_l_100:nut_num_l;
      
      public function nut_txt_score_total()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

