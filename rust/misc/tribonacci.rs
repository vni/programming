fn tribonacci(n: usize) -> u128 {
    match n {
        0 => 0,
        1 => 1,
        2 => 1,
        n => tribonacci(n-3) + tribonacci(n-2) + tribonacci(n-1),
    }
}

fn tribonacci_memo(n: usize, memo: &mut Vec<u128>) -> u128 {
    if n < memo.len() {
        return memo[n];
    }

    let tr1 = tribonacci_memo(n-3, memo);
    let tr2 = tribonacci_memo(n-2, memo);
    let tr3 = tribonacci_memo(n-1, memo);

    memo.push(tr1 + tr2 + tr3);
    return memo[memo.len() - 1];
}

fn new_memo() -> Vec<u128> {
    vec![0, 1, 1]
}

fn main() {
    let mut memo = new_memo();
    println!("first 145 tribonacci_memo:");
    for i in 0..145 {
        println!("tribonacci_memo({i}): {}", tribonacci_memo(i, &mut memo));
    }

    println!("first 145 tribonacci:");
    for i in 0..145 {
        println!("tribonacci({i}): {}", tribonacci(i));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn tribonacci_0() {
        assert_eq!(tribonacci(0), 0);
    }

    #[test]
    fn tribonacci_1() {
        assert_eq!(tribonacci(1), 1);
    }

    #[test]
    fn tribonacci_2() {
        assert_eq!(tribonacci(2), 1);
    }

    #[test]
    fn tribonacci_3() {
        assert_eq!(tribonacci(3), 2);
    }

    #[test]
    fn tribonacci_4() {
        assert_eq!(tribonacci(4), 4);
    }

    #[test]
    fn tribonacci_5() {
        assert_eq!(tribonacci(5), 7);
    }

    #[test]
    fn tribonacci_many() {
        let expected = [0, 1, 1, 2, 4, 7, 13, 24,
                        44, 81, 149, 274, 504];
        for (i, &v) in expected.iter().enumerate() {
            assert_eq!(tribonacci(i), v);
        }
    }

    #[test]
    fn tribonacci_memo_many() {
        let expected = [0, 1, 1, 2, 4, 7, 13, 24, 44, 81, 149, 274, 504, 927, 1705, 3136, 5768, 10609, 19513, 35890, 66012, 121415, 223317, 410744, 755476, 1389537, 2555757, 4700770, 8646064, 15902591, 29249425, 53798080, 98950096, 181997601, 334745777, 615693474, 1132436852, 2082876103, 3831006429, 7046319384, 12960201916, 23837527729, 43844049029, 80641778674, 148323355432, 272809183135, 501774317241, 922906855808, 1697490356184, 3122171529233, 5742568741225, 10562230626642, 19426970897100, 35731770264967, 65720971788709, 120879712950776, 222332455004452, 408933139743937, 752145307699165, 1383410902447554, 2544489349890656, 4680045560037375, 8607945812375585, 15832480722303616, 29120472094716576, 53560898629395777, 98513851446415969, 181195222170528322, 333269972246340068, 612979045863284359, 1127444240280152749, 2073693258389777176, 3814116544533214284, 7015254043203144209, 12903063846126135669, 23732434433862494162, 43650752323191774040, 80286250603180403871, 147669437360234672073, 271606440286606849984, 499562128250021925928, 918838005896863447985, 1690006574433492223897, 3108406708580377597810, 5717251288910733269692, 10515664571924603091399, 19341322569415713958901, 35574238430251050319992, 65431225571591367370292, 120346786571258131649185, 221352250573100549339469, 407130262715950048358946, 748829299860308729347600, 1377311813149359327046015, 2533271375725618104752561, 4659412488735286161146176, 8569995677610263592944752, 15762679542071167858843489, 28992087708416717612934417, 53324762928098149064722658, 98079530178586034536500564, 180396380815100901214157639, 331800673921785084815380861, 610276584915472020566039064, 1122473639652358006595577564, 2064550898489615111976997489, 3797301123057445139138614117, 6984325661199418257711189170, 12846177682746478508826800776, 23627804467003341905676604063, 43458307810949238672214594009, 79932289960699059086717998848, 147018402238651639664609196920, 270409000010299937423541789777, 497359692209650636174868985545, 914787094458602213263019972242, 1682555786678552786861430747564, 3094702573346805636299319705351, 5692045454483960636423770425157, 10469303814509319059584520878072, 19256051842340085332307611008580, 35417401111333365028315902311809, 65142756768182769420208034198461, 119816209721856219780831547518850, 220376367601372354229355484029120, 405335334091411343430395065746431, 745527911414639917440582097294401, 1371239613107423615100332647069952, 2522102858613474875971309810110784, 4638870383135538408512224554475137, 8532212854856436899583867011655873, 15693186096605450184067401376241794, 28864269334597425492163492942372804, 53089668286059312575814761330270471, 97647123717262188252045655648885069, 179601061337918926320023909921528344, 330337853341240427147884326900683884, 607586038396421541719953892471097297, 1117524953075580895187862129293309525, 2055448844813242864055700348665090706, 3780559836285245300963516370429497528, 6953533634174069060207078848387897759, 12789542315272557225226295567482485993, 23523635785731871586396890786299881280, 43266711735178497871830265202170265032];
        let mut memo = new_memo();
        for (i, &v) in expected.iter().enumerate() {
            assert_eq!(tribonacci_memo(i, &mut memo), v);
        }
    }
}
