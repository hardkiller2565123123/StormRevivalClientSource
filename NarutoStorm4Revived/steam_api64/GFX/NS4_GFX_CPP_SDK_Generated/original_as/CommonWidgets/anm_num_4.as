package duel_boss4_fla
{
   import flash.display.MovieClip;
   import script.num_s.nut_num_s;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public dynamic class anm_num_4 extends MovieClip
   {
      
      public var mc_num1:nut_num_s;
      
      public var mc_num10:nut_num_s;
      
      public var mc_num100:nut_num_s;
      
      public var mc_num1000:nut_num_s;
      
      public var mc_num10000:nut_num_s;
      
      public var mc_num100000:nut_num_s;
      
      public function anm_num_4()
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

