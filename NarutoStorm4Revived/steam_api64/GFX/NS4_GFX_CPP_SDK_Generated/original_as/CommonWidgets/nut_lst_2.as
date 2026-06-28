package start_change_fla
{
   import flash.display.MovieClip;
   import script.start_change.nut_shift;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public dynamic class nut_lst_2 extends MovieClip
   {
      
      public var mc_list2:nut_shift;
      
      public var mc_list3:nut_shift;
      
      public var mc_list1:nut_shift;
      
      public function nut_lst_2()
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

