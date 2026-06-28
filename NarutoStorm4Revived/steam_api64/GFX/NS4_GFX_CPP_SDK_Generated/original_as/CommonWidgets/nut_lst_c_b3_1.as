package script.hist_cmn
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol25")]
   public class nut_lst_c_b3_1 extends start_list_base
   {
      
      public var mc_btl1:MovieClip;
      
      public var mc_btl2:MovieClip;
      
      public var mc_btl3:MovieClip;
      
      public var mc_c1:MovieClip;
      
      public var mc_c2:MovieClip;
      
      public function nut_lst_c_b3_1()
      {
         super();
         addFrameScript(29,this.frame30,33,this.frame34,37,this.frame38,41,this.frame42,45,this.frame46,76,this.frame77);
      }
      
      override public function CreateStartPointList() : *
      {
         m_startPointList.push(MovieClip(this["mc_c1"]));
         m_startPointList.push(MovieClip(this["mc_btl1"]));
         m_startPointList.push(MovieClip(this["mc_c2"]));
         m_startPointList.push(MovieClip(this["mc_btl2"]));
         m_startPointList.push(MovieClip(this["mc_btl3"]));
      }
      
      internal function frame30() : *
      {
         this.stop();
      }
      
      internal function frame34() : *
      {
         this.stop();
      }
      
      internal function frame38() : *
      {
         gotoAndStop("loop");
      }
      
      internal function frame42() : *
      {
         this.stop();
      }
      
      internal function frame46() : *
      {
         gotoAndStop("loop");
      }
      
      internal function frame77() : *
      {
         this.stop();
      }
   }
}

