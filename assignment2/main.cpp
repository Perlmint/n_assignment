#include <random>
#include "vector.hpp"
#include <algorithm>
#include <cassert>

using test_type = int;
void dataSample(std::vector<test_type> &data);

int main(int /* argc */, char * /* argv */[])
{
  std::vector<test_type> data;
  dataSample(data);

  Vector<test_type> vector;
  for (const auto &datum : data)
  {
    vector.push_back(datum);
  }

  std::sort(data.begin(), data.end());
  auto itr = data.begin();
  while (!vector.empty())
  {
    assert(vector.front() == *itr);
    ++itr;
    vector.pop_back();
    if (vector.size() == 4)
    {
      break;
    }
  }

  auto endOfData = data.end();

  while(!vector.empty())
  {
    assert(std::find(itr, endOfData, vector.front()) != endOfData);
    vector.pop_back();
  }

  return 0;
}

void dataSample(std::vector<test_type> &data)
{
  data.push_back(55807);
  data.push_back(62220);
  data.push_back(63396);
  data.push_back(21973);
  data.push_back(50641);
  data.push_back(25617);
  data.push_back(33962);
  data.push_back(16949);
  data.push_back(12716);
  data.push_back(47327);
  data.push_back(34099);
  data.push_back(25425);
  data.push_back(20509);
  data.push_back(28329);
  data.push_back(8764);
  data.push_back(43595);
  data.push_back(55772);
  data.push_back(16364);
  data.push_back(49207);
  data.push_back(30883);
  data.push_back(2235);
  data.push_back(16172);
  data.push_back(31431);
  data.push_back(2568);
  data.push_back(49731);
  data.push_back(27564);
  data.push_back(25264);
  data.push_back(45386);
  data.push_back(29013);
  data.push_back(59274);
  data.push_back(46054);
  data.push_back(7095);
  data.push_back(36482);
  data.push_back(27806);
  data.push_back(43544);
  data.push_back(25309);
  data.push_back(10587);
  data.push_back(41988);
  data.push_back(58379);
  data.push_back(25775);
  data.push_back(61209);
  data.push_back(60053);
  data.push_back(23233);
  data.push_back(39135);
  data.push_back(13853);
  data.push_back(57018);
  data.push_back(35300);
  data.push_back(20706);
  data.push_back(10852);
  data.push_back(29402);
  data.push_back(47985);
  data.push_back(40751);
  data.push_back(29995);
  data.push_back(22645);
  data.push_back(2364);
  data.push_back(23608);
  data.push_back(19223);
  data.push_back(44356);
  data.push_back(3355);
  data.push_back(19817);
  data.push_back(30121);
  data.push_back(23123);
  data.push_back(24173);
  data.push_back(35516);
  data.push_back(30662);
  data.push_back(45811);
  data.push_back(26226);
  data.push_back(58378);
  data.push_back(8069);
  data.push_back(15443);
  data.push_back(44001);
  data.push_back(29423);
  data.push_back(19324);
  data.push_back(39115);
  data.push_back(55046);
  data.push_back(25608);
  data.push_back(30712);
  data.push_back(5876);
  data.push_back(61829);
  data.push_back(35871);
  data.push_back(61604);
  data.push_back(33667);
  data.push_back(58605);
  data.push_back(49791);
  data.push_back(46832);
  data.push_back(17313);
  data.push_back(43686);
  data.push_back(12996);
  data.push_back(33160);
  data.push_back(31764);
  data.push_back(11404);
  data.push_back(10812);
  data.push_back(26449);
  data.push_back(56068);
  data.push_back(35437);
  data.push_back(62427);
  data.push_back(12634);
  data.push_back(28756);
  data.push_back(50934);
  data.push_back(65285);
  data.push_back(11733);
  data.push_back(32772);
  data.push_back(20186);
  data.push_back(53183);
  data.push_back(2957);
  data.push_back(27604);
  data.push_back(38864);
  data.push_back(25513);
  data.push_back(17015);
  data.push_back(332);
  data.push_back(31148);
  data.push_back(54368);
  data.push_back(12615);
  data.push_back(61101);
  data.push_back(47996);
  data.push_back(31830);
  data.push_back(48925);
  data.push_back(30268);
  data.push_back(15298);
  data.push_back(57114);
  data.push_back(50360);
  data.push_back(18398);
  data.push_back(52750);
  data.push_back(2233);
  data.push_back(3130);
  data.push_back(18924);
  data.push_back(25961);
  data.push_back(31362);
  data.push_back(65068);
  data.push_back(64757);
  data.push_back(58367);
  data.push_back(28690);
  data.push_back(60195);
  data.push_back(15863);
  data.push_back(29959);
  data.push_back(60992);
  data.push_back(33156);
  data.push_back(29997);
  data.push_back(2602);
  data.push_back(58266);
  data.push_back(65338);
  data.push_back(57380);
  data.push_back(58775);
  data.push_back(1772);
  data.push_back(21437);
  data.push_back(24455);
  data.push_back(45801);
  data.push_back(25307);
  data.push_back(23176);
  data.push_back(58406);
  data.push_back(38180);
  data.push_back(11486);
  data.push_back(21895);
  data.push_back(23233);
  data.push_back(35979);
  data.push_back(57645);
  data.push_back(64336);
  data.push_back(35654);
  data.push_back(9043);
  data.push_back(31014);
  data.push_back(39637);
  data.push_back(49680);
  data.push_back(23089);
  data.push_back(37095);
  data.push_back(55340);
  data.push_back(38316);
  data.push_back(60590);
  data.push_back(9065);
  data.push_back(17601);
  data.push_back(46852);
  data.push_back(38620);
  data.push_back(46433);
  data.push_back(55315);
  data.push_back(47251);
  data.push_back(36011);
  data.push_back(25744);
  data.push_back(2365);
  data.push_back(40210);
  data.push_back(22422);
  data.push_back(59617);
  data.push_back(59275);
  data.push_back(52510);
  data.push_back(36950);
  data.push_back(34339);
  data.push_back(50714);
  data.push_back(41148);
  data.push_back(13828);
  data.push_back(18685);
  data.push_back(50918);
  data.push_back(29604);
  data.push_back(35490);
  data.push_back(65119);
  data.push_back(63363);
  data.push_back(20658);
  data.push_back(12316);
  data.push_back(39012);
  data.push_back(62805);
  data.push_back(43891);
  data.push_back(17901);
  data.push_back(5087);
  data.push_back(43701);
  data.push_back(33786);
  data.push_back(34518);
  data.push_back(10623);
  data.push_back(55167);
  data.push_back(25035);
  data.push_back(21579);
  data.push_back(9982);
  data.push_back(28972);
  data.push_back(28230);
  data.push_back(64409);
  data.push_back(44564);
  data.push_back(25741);
  data.push_back(21207);
  data.push_back(33171);
  data.push_back(24472);
  data.push_back(10993);
  data.push_back(9610);
  data.push_back(6108);
  data.push_back(54950);
  data.push_back(4882);
  data.push_back(38414);
  data.push_back(32289);
  data.push_back(29411);
  data.push_back(28319);
  data.push_back(53851);
  data.push_back(65287);
  data.push_back(48150);
  data.push_back(17110);
  data.push_back(47288);
  data.push_back(55710);
  data.push_back(31336);
  data.push_back(52144);
  data.push_back(56449);
  data.push_back(31176);
  data.push_back(25395);
  data.push_back(31258);
  data.push_back(18714);
  data.push_back(58220);
  data.push_back(35453);
  data.push_back(11723);
  data.push_back(29883);
  data.push_back(35131);
  data.push_back(29423);
  data.push_back(1477);
  data.push_back(19514);
  data.push_back(9739);
  data.push_back(48457);
  data.push_back(36243);
  data.push_back(17280);
  data.push_back(17506);
  data.push_back(40451);
  data.push_back(56449);
  data.push_back(14521);
  data.push_back(19733);
  data.push_back(28461);
  data.push_back(43508);
  data.push_back(49245);
  data.push_back(53120);
  data.push_back(30549);
  data.push_back(59816);
  data.push_back(32013);
  data.push_back(31708);
  data.push_back(51210);
  data.push_back(44623);
  data.push_back(57993);
  data.push_back(64333);
  data.push_back(46319);
  data.push_back(40369);
  data.push_back(4941);
  data.push_back(40721);
  data.push_back(58202);
  data.push_back(35962);
  data.push_back(4107);
  data.push_back(37122);
  data.push_back(21461);
  data.push_back(20147);
  data.push_back(39097);
  data.push_back(14224);
  data.push_back(3963);
  data.push_back(27958);
  data.push_back(19046);
  data.push_back(3086);
  data.push_back(51925);
  data.push_back(18891);
  data.push_back(64000);
  data.push_back(32128);
  data.push_back(52386);
  data.push_back(16);
  data.push_back(44903);
  data.push_back(10644);
  data.push_back(37338);
  data.push_back(9065);
  data.push_back(49871);
  data.push_back(14473);
  data.push_back(34385);
  data.push_back(52415);
  data.push_back(56813);
  data.push_back(19577);
  data.push_back(28093);
  data.push_back(16367);
  data.push_back(2106);
  data.push_back(2453);
  data.push_back(8702);
  data.push_back(28925);
  data.push_back(51656);
  data.push_back(3684);
  data.push_back(59389);
  data.push_back(40635);
  data.push_back(46374);
  data.push_back(37449);
  data.push_back(56769);
  data.push_back(28238);
  data.push_back(30084);
  data.push_back(39735);
  data.push_back(21738);
  data.push_back(36588);
  data.push_back(52611);
  data.push_back(1453);
  data.push_back(56902);
  data.push_back(46251);
  data.push_back(58093);
  data.push_back(22381);
  data.push_back(26147);
  data.push_back(51841);
  data.push_back(38155);
  data.push_back(31182);
  data.push_back(32475);
  data.push_back(35745);
  data.push_back(24084);
  data.push_back(5908);
  data.push_back(14893);
  data.push_back(28682);
  data.push_back(43941);
  data.push_back(50469);
  data.push_back(6778);
  data.push_back(8188);
  data.push_back(31918);
  data.push_back(6707);
  data.push_back(43380);
  data.push_back(34343);
  data.push_back(31478);
  data.push_back(55436);
  data.push_back(29067);
  data.push_back(40690);
  data.push_back(63438);
  data.push_back(27005);
  data.push_back(6580);
  data.push_back(29004);
  data.push_back(59087);
  data.push_back(16535);
  data.push_back(28343);
  data.push_back(16123);
  data.push_back(21381);
  data.push_back(30812);
  data.push_back(60548);
  data.push_back(32803);
  data.push_back(32820);
  data.push_back(3631);
  data.push_back(38154);
  data.push_back(27730);
  data.push_back(55235);
  data.push_back(24995);
  data.push_back(41292);
  data.push_back(40823);
  data.push_back(57954);
  data.push_back(17738);
  data.push_back(55726);
  data.push_back(22190);
  data.push_back(38528);
  data.push_back(22720);
  data.push_back(398);
  data.push_back(42497);
  data.push_back(24921);
  data.push_back(42206);
  data.push_back(50722);
  data.push_back(61540);
  data.push_back(51623);
  data.push_back(52655);
  data.push_back(51824);
  data.push_back(50370);
  data.push_back(51823);
  data.push_back(39263);
  data.push_back(49421);
  data.push_back(25186);
  data.push_back(17687);
  data.push_back(57513);
  data.push_back(40700);
  data.push_back(35491);
  data.push_back(19669);
  data.push_back(3834);
  data.push_back(9981);
  data.push_back(60906);
  data.push_back(45);
  data.push_back(55592);
  data.push_back(12999);
  data.push_back(60649);
  data.push_back(26782);
  data.push_back(40728);
  data.push_back(54220);
  data.push_back(8683);
  data.push_back(61471);
  data.push_back(44020);
  data.push_back(37694);
  data.push_back(435);
  data.push_back(5868);
  data.push_back(4317);
  data.push_back(26535);
  data.push_back(54079);
  data.push_back(15246);
  data.push_back(38370);
  data.push_back(57019);
  data.push_back(21460);
  data.push_back(29594);
  data.push_back(24353);
  data.push_back(1973);
  data.push_back(60462);
  data.push_back(14558);
  data.push_back(49267);
  data.push_back(56389);
  data.push_back(19589);
  data.push_back(40369);
  data.push_back(882);
  data.push_back(53146);
  data.push_back(40979);
  data.push_back(59372);
  data.push_back(42737);
  data.push_back(19027);
  data.push_back(37993);
  data.push_back(38802);
  data.push_back(31443);
  data.push_back(35719);
  data.push_back(5063);
  data.push_back(49278);
  data.push_back(5689);
  data.push_back(23265);
  data.push_back(24284);
  data.push_back(32075);
  data.push_back(5581);
  data.push_back(64917);
  data.push_back(51711);
  data.push_back(15227);
  data.push_back(35300);
  data.push_back(3860);
  data.push_back(45168);
  data.push_back(18622);
  data.push_back(30640);
  data.push_back(27135);
  data.push_back(9784);
  data.push_back(46578);
  data.push_back(31866);
  data.push_back(32311);
  data.push_back(35755);
  data.push_back(16646);
  data.push_back(54934);
  data.push_back(41744);
  data.push_back(40512);
  data.push_back(27937);
  data.push_back(48483);
  data.push_back(8427);
  data.push_back(21714);
  data.push_back(24207);
  data.push_back(14946);
  data.push_back(61224);
  data.push_back(27657);
  data.push_back(27732);
  data.push_back(30376);
  data.push_back(49786);
  data.push_back(34756);
  data.push_back(51274);
  data.push_back(14650);
  data.push_back(10300);
  data.push_back(3145);
  data.push_back(29338);
  data.push_back(33681);
  data.push_back(8374);
  data.push_back(65393);
  data.push_back(19863);
  data.push_back(21001);
  data.push_back(34503);
  data.push_back(22834);
  data.push_back(63885);
  data.push_back(30696);
  data.push_back(14302);
  data.push_back(63270);
  data.push_back(1137);
  data.push_back(38521);
  data.push_back(40758);
  data.push_back(21826);
  data.push_back(43817);
  data.push_back(48925);
  data.push_back(4819);
  data.push_back(12381);
  data.push_back(33216);
  data.push_back(4016);
  data.push_back(23856);
  data.push_back(58443);
  data.push_back(53627);
  data.push_back(52687);
  data.push_back(44059);
  data.push_back(1486);
  data.push_back(46625);
  data.push_back(222);
  data.push_back(53356);
  data.push_back(44230);
  data.push_back(62257);
  data.push_back(33459);
  data.push_back(22320);
  data.push_back(1162);
  data.push_back(12240);
  data.push_back(58301);
  data.push_back(12494);
  data.push_back(17341);
  data.push_back(31773);
  data.push_back(8021);
  data.push_back(35824);
  data.push_back(41442);
  data.push_back(60205);
  data.push_back(20589);
  data.push_back(40875);
  data.push_back(26316);
  data.push_back(45186);
  data.push_back(24316);
  data.push_back(56346);
  data.push_back(52764);
  data.push_back(37048);
  data.push_back(5228);
  data.push_back(28782);
  data.push_back(19476);
  data.push_back(57028);
  data.push_back(34503);
  data.push_back(30443);
  data.push_back(46252);
  data.push_back(62468);
  data.push_back(26662);
  data.push_back(1607);
  data.push_back(32408);
  data.push_back(48512);
  data.push_back(34524);
  data.push_back(2230);
  data.push_back(32086);
  data.push_back(35920);
  data.push_back(22569);
  data.push_back(61558);
  data.push_back(3761);
  data.push_back(39980);
  data.push_back(63998);
  data.push_back(18057);
  data.push_back(2846);
  data.push_back(26414);
  data.push_back(22640);
  data.push_back(34510);
  data.push_back(51642);
  data.push_back(8705);
  data.push_back(4798);
  data.push_back(11863);
  data.push_back(25120);
  data.push_back(12646);
  data.push_back(39529);
  data.push_back(49561);
  data.push_back(55380);
  data.push_back(28066);
  data.push_back(47300);
  data.push_back(23853);
  data.push_back(31179);
  data.push_back(6307);
  data.push_back(16036);
  data.push_back(20430);
  data.push_back(63617);
  data.push_back(53149);
  data.push_back(22798);
  data.push_back(6648);
  data.push_back(39050);
  data.push_back(46410);
  data.push_back(33682);
  data.push_back(27110);
  data.push_back(3277);
  data.push_back(12213);
  data.push_back(58440);
  data.push_back(64374);
  data.push_back(56944);
  data.push_back(11057);
  data.push_back(50333);
  data.push_back(60311);
  data.push_back(7614);
  data.push_back(19896);
  data.push_back(22628);
  data.push_back(64993);
  data.push_back(7775);
  data.push_back(14361);
  data.push_back(5480);
  data.push_back(37245);
  data.push_back(10781);
  data.push_back(20649);
  data.push_back(50677);
  data.push_back(41984);
  data.push_back(23611);
  data.push_back(14256);
  data.push_back(551);
  data.push_back(10504);
  data.push_back(47940);
  data.push_back(3055);
  data.push_back(41272);
  data.push_back(13061);
  data.push_back(13100);
  data.push_back(47581);
  data.push_back(62059);
  data.push_back(34021);
  data.push_back(39768);
  data.push_back(29561);
  data.push_back(44654);
  data.push_back(29159);
  data.push_back(27656);
  data.push_back(732);
  data.push_back(57543);
  data.push_back(42885);
  data.push_back(64362);
  data.push_back(49957);
  data.push_back(22212);
  data.push_back(31890);
  data.push_back(34643);
  data.push_back(19654);
  data.push_back(55950);
  data.push_back(1269);
  data.push_back(51772);
  data.push_back(42379);
  data.push_back(48515);
  data.push_back(38954);
  data.push_back(14077);
  data.push_back(16147);
  data.push_back(50801);
  data.push_back(38348);
  data.push_back(10842);
  data.push_back(34108);
  data.push_back(23601);
  data.push_back(65193);
  data.push_back(5876);
  data.push_back(1917);
  data.push_back(36801);
  data.push_back(3023);
  data.push_back(39902);
  data.push_back(19345);
  data.push_back(525);
  data.push_back(29930);
  data.push_back(4263);
  data.push_back(33159);
  data.push_back(62056);
  data.push_back(33400);
  data.push_back(59107);
  data.push_back(8825);
  data.push_back(52710);
  data.push_back(62384);
  data.push_back(43590);
  data.push_back(44707);
  data.push_back(44993);
  data.push_back(6284);
  data.push_back(42342);
  data.push_back(29733);
  data.push_back(23405);
  data.push_back(33143);
  data.push_back(61073);
  data.push_back(569);
  data.push_back(38664);
  data.push_back(63944);
  data.push_back(42151);
  data.push_back(38050);
  data.push_back(60151);
  data.push_back(10939);
  data.push_back(33812);
  data.push_back(11951);
  data.push_back(24519);
  data.push_back(3019);
  data.push_back(3563);
  data.push_back(58750);
  data.push_back(12988);
  data.push_back(58026);
  data.push_back(48191);
  data.push_back(62606);
  data.push_back(21756);
  data.push_back(11294);
  data.push_back(45775);
  data.push_back(31818);
  data.push_back(6465);
  data.push_back(12471);
  data.push_back(23646);
  data.push_back(61190);
  data.push_back(39536);
  data.push_back(55646);
  data.push_back(52973);
  data.push_back(36765);
  data.push_back(17361);
  data.push_back(20110);
  data.push_back(50099);
  data.push_back(22509);
  data.push_back(834);
  data.push_back(54796);
  data.push_back(1242);
  data.push_back(10474);
  data.push_back(31817);
  data.push_back(43895);
  data.push_back(31830);
  data.push_back(45307);
  data.push_back(55027);
  data.push_back(19367);
  data.push_back(42874);
  data.push_back(59646);
  data.push_back(44997);
  data.push_back(31272);
  data.push_back(44447);
  data.push_back(34252);
  data.push_back(835);
  data.push_back(31365);
  data.push_back(62484);
  data.push_back(39659);
  data.push_back(6983);
  data.push_back(53558);
  data.push_back(16513);
  data.push_back(16102);
  data.push_back(52950);
  data.push_back(46171);
  data.push_back(14599);
  data.push_back(41871);
  data.push_back(14513);
  data.push_back(20542);
  data.push_back(5901);
  data.push_back(3899);
  data.push_back(29464);
  data.push_back(24500);
  data.push_back(9602);
  data.push_back(1306);
  data.push_back(48752);
  data.push_back(54598);
  data.push_back(1984);
  data.push_back(51872);
  data.push_back(65448);
  data.push_back(16654);
  data.push_back(14269);
  data.push_back(50184);
  data.push_back(29818);
  data.push_back(57787);
  data.push_back(53290);
  data.push_back(17222);
  data.push_back(37597);
  data.push_back(28219);
  data.push_back(45816);
  data.push_back(34769);
  data.push_back(37474);
  data.push_back(47341);
  data.push_back(21239);
  data.push_back(20844);
  data.push_back(25236);
  data.push_back(24007);
  data.push_back(47963);
  data.push_back(44461);
  data.push_back(46714);
  data.push_back(269);
  data.push_back(56838);
  data.push_back(17050);
  data.push_back(29541);
  data.push_back(49357);
  data.push_back(30595);
  data.push_back(12137);
  data.push_back(31691);
  data.push_back(45132);
  data.push_back(35977);
  data.push_back(55446);
  data.push_back(58148);
  data.push_back(36135);
  data.push_back(43011);
  data.push_back(19138);
  data.push_back(17877);
  data.push_back(55624);
  data.push_back(42643);
  data.push_back(10706);
  data.push_back(37056);
  data.push_back(47642);
  data.push_back(19110);
  data.push_back(40584);
  data.push_back(61853);
  data.push_back(49058);
  data.push_back(59152);
  data.push_back(29937);
  data.push_back(59563);
  data.push_back(2874);
  data.push_back(30929);
  data.push_back(54674);
  data.push_back(7554);
  data.push_back(15705);
  data.push_back(1168);
  data.push_back(22000);
  data.push_back(53299);
  data.push_back(38808);
  data.push_back(15675);
  data.push_back(58229);
  data.push_back(18398);
  data.push_back(17836);
  data.push_back(56661);
  data.push_back(48457);
  data.push_back(29685);
  data.push_back(64563);
  data.push_back(11745);
  data.push_back(9813);
  data.push_back(29848);
  data.push_back(26949);
  data.push_back(7425);
  data.push_back(1062);
  data.push_back(54533);
  data.push_back(55775);
  data.push_back(13087);
  data.push_back(64202);
  data.push_back(5920);
  data.push_back(2562);
  data.push_back(12375);
  data.push_back(10086);
  data.push_back(1373);
  data.push_back(9146);
  data.push_back(10625);
  data.push_back(65005);
  data.push_back(32925);
  data.push_back(27025);
  data.push_back(59761);
  data.push_back(60145);
  data.push_back(53994);
  data.push_back(49828);
  data.push_back(32540);
  data.push_back(37779);
  data.push_back(39730);
  data.push_back(57641);
  data.push_back(20726);
  data.push_back(6831);
  data.push_back(64257);
  data.push_back(28408);
  data.push_back(9213);
  data.push_back(13564);
  data.push_back(30414);
  data.push_back(42043);
  data.push_back(65072);
  data.push_back(62491);
  data.push_back(32643);
  data.push_back(39888);
  data.push_back(47417);
  data.push_back(65134);
  data.push_back(16006);
  data.push_back(19610);
  data.push_back(44084);
  data.push_back(64479);
  data.push_back(8054);
  data.push_back(59434);
  data.push_back(30903);
  data.push_back(24577);
  data.push_back(18179);
  data.push_back(25044);
  data.push_back(6865);
  data.push_back(51743);
  data.push_back(47041);
  data.push_back(2566);
  data.push_back(45547);
  data.push_back(50969);
  data.push_back(19815);
  data.push_back(61806);
  data.push_back(9009);
  data.push_back(57318);
  data.push_back(27103);
  data.push_back(9002);
  data.push_back(57811);
  data.push_back(16614);
  data.push_back(33311);
  data.push_back(35883);
  data.push_back(46960);
  data.push_back(60972);
  data.push_back(53793);
  data.push_back(61786);
  data.push_back(57482);
  data.push_back(11781);
  data.push_back(10212);
  data.push_back(22357);
  data.push_back(40280);
  data.push_back(50845);
  data.push_back(23797);
  data.push_back(50232);
  data.push_back(7656);
  data.push_back(35546);
  data.push_back(24915);
  data.push_back(50628);
  data.push_back(30856);
  data.push_back(56520);
  data.push_back(38494);
  data.push_back(44462);
  data.push_back(56723);
  data.push_back(11516);
  data.push_back(34521);
  data.push_back(51832);
  data.push_back(25271);
  data.push_back(19289);
  data.push_back(41746);
  data.push_back(40333);
  data.push_back(14585);
  data.push_back(34347);
  data.push_back(28298);
  data.push_back(54090);
  data.push_back(53410);
  data.push_back(36466);
  data.push_back(33135);
  data.push_back(49927);
  data.push_back(42887);
  data.push_back(10197);
  data.push_back(57284);
  data.push_back(36731);
  data.push_back(44583);
  data.push_back(58001);
  data.push_back(45282);
  data.push_back(40424);
  data.push_back(5408);
  data.push_back(48416);
  data.push_back(30154);
  data.push_back(26461);
  data.push_back(55700);
  data.push_back(47080);
  data.push_back(59336);
  data.push_back(22416);
  data.push_back(64651);
  data.push_back(53820);
  data.push_back(25988);
  data.push_back(26483);
  data.push_back(15345);
  data.push_back(52132);
  data.push_back(2166);
  data.push_back(22017);
  data.push_back(2387);
  data.push_back(53670);
  data.push_back(40272);
  data.push_back(37617);
  data.push_back(26157);
  data.push_back(24422);
  data.push_back(54647);
  data.push_back(1886);
  data.push_back(63968);
  data.push_back(57192);
  data.push_back(13909);
  data.push_back(58050);
  data.push_back(50408);
  data.push_back(61116);
  data.push_back(44390);
  data.push_back(2998);
  data.push_back(8422);
  data.push_back(7742);
  data.push_back(64347);
  data.push_back(18215);
  data.push_back(54646);
  data.push_back(23205);
  data.push_back(3277);
  data.push_back(3913);
  data.push_back(21942);
  data.push_back(3771);
  data.push_back(52441);
  data.push_back(56769);
  data.push_back(25600);
  data.push_back(54556);
  data.push_back(48145);
  data.push_back(64212);
  data.push_back(27048);
  data.push_back(37927);
  data.push_back(38566);
  data.push_back(18379);
  data.push_back(33064);
  data.push_back(62348);
  data.push_back(31683);
  data.push_back(20433);
  data.push_back(60684);
  data.push_back(42671);
  data.push_back(19093);
  data.push_back(290);
  data.push_back(57700);
  data.push_back(17602);
  data.push_back(48819);
  data.push_back(55424);
  data.push_back(12461);
  data.push_back(14965);
  data.push_back(7678);
  data.push_back(13517);
  data.push_back(34496);
  data.push_back(43004);
  data.push_back(39807);
  data.push_back(19946);
  data.push_back(53907);
  data.push_back(4649);
  data.push_back(12204);
  data.push_back(6214);
  data.push_back(32672);
  data.push_back(35882);
  data.push_back(50123);
  data.push_back(22960);
  data.push_back(24843);
  data.push_back(1597);
  data.push_back(34882);
  data.push_back(59695);
  data.push_back(26035);
  data.push_back(52701);
  data.push_back(32391);
  data.push_back(17775);
}