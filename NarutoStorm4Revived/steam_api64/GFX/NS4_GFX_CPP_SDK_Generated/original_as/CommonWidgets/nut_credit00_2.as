package script.xcmn_unset
{
   import flash.display.MovieClip;
   import flash.geom.ColorTransform;
   
   public class nut_credit00 extends MovieClip
   {
      
      private var credit:MovieClip = null;
      
      public function nut_credit00()
      {
         super();
         this.credit = MovieClip(getChildByName("mc_credit00"));
      }
      
      public function SetColorDeepBlue() : *
      {
         var _loc1_:ColorTransform = null;
         if(this.credit != null)
         {
            _loc1_ = new ColorTransform();
            _loc1_.color = 85;
            this.credit.transform.colorTransform = _loc1_;
         }
      }
   }
}

